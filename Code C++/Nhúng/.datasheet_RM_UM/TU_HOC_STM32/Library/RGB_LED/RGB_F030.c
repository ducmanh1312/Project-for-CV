#include "stm32f0xx_conf.h"
#include "Core.h"
#include "RGB_F030.h"

uint8_t rgb_data_buff[3 * RGB_NUM_LEDS];

/**********************************************************************/
#if defined (RGB_LED_PIN_A2)
  #define RGB_LED_PIN      2
#elif defined (RGB_LED_PIN_A9)
  #define RGB_LED_PIN      9
#elif defined (RGB_LED_PIN_A14)
  #define RGB_LED_PIN      14
#endif

#define GPIO_Speed_RGB_LED_PIN   GPIO_Speed_10MHz

#if defined (RGB_MODE_DMA_CHANNEL_2) || \
    defined (RGB_MODE_DMA_CHANNEL_4)

  #define RGB_MODE_DMA
#endif

/**********************************************************************/
uint32_t rgb_brightness = 1;  // default

void RGB_setBrightness(uint32_t brightness) {
  rgb_brightness = brightness;
}

uint32_t RGB_getBrightness(uint32_t brightness) {
  return rgb_brightness;
}

/**********************************************************************/
#ifdef RGB_MODE_DMA
  #define RGB_DMA_USART_BUFF_SIZE   (8 * 2)
  uint8_t rgb_dma_usart_buff[RGB_DMA_USART_BUFF_SIZE];

  #ifdef RGB_MODE_DMA_CHANNEL_2
    #define RGB_DMA_CHANNEL  DMA1_Channel2
    #define RGB_DMA_FLAG_TC  DMA1_FLAG_TC2
    #define RGB_DMA_FLAG_HT  DMA1_FLAG_HT2
    #define RGB_DMA_IRQ      DMA1_Channel2_3_IRQn
  #endif

  #ifdef  RGB_MODE_DMA_CHANNEL_4
    #define RGB_DMA_CHANNEL  DMA1_Channel4
    #define RGB_DMA_FLAG_TC  DMA1_FLAG_TC4
    #define RGB_DMA_FLAG_HT  DMA1_FLAG_HT4
    #define RGB_DMA_IRQ      DMA1_Channel4_5_IRQn
  #endif

  #define RGB_DMA_CCR    ( DMA_DIR_PeripheralDST        \
                         | DMA_PeripheralInc_Disable    \
                         | DMA_MemoryInc_Enable         \
                         | DMA_PeripheralDataSize_Byte  \
                         | DMA_MemoryDataSize_Byte      \
                         | DMA_Mode_Circular            \
                         | DMA_Priority_High            \
                         | DMA_M2M_Disable              \
                         | DMA_CCR_HTIE                 \
                         | DMA_CCR_TCIE                 \
                         | DMA_CCR_EN)

  #define RGB_DMA_CNDTR  (RGB_DMA_USART_BUFF_SIZE)
  #define RGB_DMA_CPAR   ((uint32_t)(&USART1->TDR))
  #define RGB_DMA_CMAR   ((uint32_t)(&rgb_dma_usart_buff))

#endif  // RGB_MODE_DMA


/**********************************************************************/
#ifdef RGB_DMA_BACKUP
  uint32_t rgb_dma1_user_ccr;
  uint32_t rgb_dma1_user_cpar;
  uint32_t rgb_dma1_user_cmar;
  uint32_t rgb_syscfg_user_cfgr1;

  void RGB_DMA_backup()
  {
    rgb_syscfg_user_cfgr1 = SYSCFG->CFGR1;
    rgb_dma1_user_ccr   = RGB_DMA_CHANNEL->CCR;
    rgb_dma1_user_cpar  = RGB_DMA_CHANNEL->CPAR;
    rgb_dma1_user_cmar  = RGB_DMA_CHANNEL->CMAR;
  }

  void RGB_DMA_restore()
  {
    SYSCFG->CFGR1 = rgb_syscfg_user_cfgr1;
    RGB_DMA_CHANNEL->CCR   = rgb_dma1_user_ccr;
    RGB_DMA_CHANNEL->CPAR  = rgb_dma1_user_cpar;
    RGB_DMA_CHANNEL->CMAR  = rgb_dma1_user_cmar;
  }

#else
  void RGB_DMA_backup()  {}
  void RGB_DMA_restore() {}
#endif  // RGB_DMA_BACKUP


/**********************************************************************/
#define RGB_USART1_CR1    ( USART_WordLength_8b   \
                          | USART_Parity_No       \
                          | USART_Mode_Tx         \
                          | USART_CR1_OVER8       \
                          | USART_CR1_UE )

#define RGB_USART1_CR2    ( USART_StopBits_1      \
                          | USART_CR2_MSBFIRST    \
                          | USART_InvPin_Tx )

#define RGB_USART1_CR3    (USART_HardwareFlowControl_None)

/* 171205: test STM32F030_USART1_TX vs 3 modules WS2818B

 USART1 |  baudrate  |     pulse width (us)         |   Vcc WS2818B   |
  div   |   (MHz)    | 1bit | 3bit | 4bit | average |  3.3V  |  5V    |
----------------------------------------------------------------------|
  0x1B  | 3,555,556  | 0.28 | 0.84 | 1.13 |	 0.94   |  bad   |  bad   |
  0x1C  | 3,428,571  | 0.29 | 0.88 | 1.17 |  0.97   |  bad   |  good  |
  0x1D  | 3,310,345  | 0.30 | 0.91 | 1.21 |  1.01   |  bad   |  good  |

  0x1E  | 3,200,000  | 0.31	| 0.94 | 1.25 |  1.04   |  good  |  good  |
  0x1F	| 3,096,774  | 0.32	| 0.97 | 1.29 |  1.08   |  good  |  good  |
  0x20	| 3,000,000  | 0.33	| 1.00 | 1.33 |  1.11   |  good  |  good  |
  ...
  0x25	| 2,621,277  | 0.38 | 1.14 | 1.53 |  1.27   |  good  |  good  |  (TB cộng)
  0x26	| 2,556,593  | 0.39 | 1.17 | 1.56 |  1.30   |  good  |  good  |  (TB nhân)
  ...
  0x2E	| 2,086,957  | 0.48 | 1.44 | 1.92 |	 1.60   |  good  |  good  |
  0x2F	| 2,042,553  | 0.49 | 1.47 | 1.96 |  1.63   |  good  |  good  |

  0x30  | 2,000,000  | 0.50	| 1.50 | 2.00 |  1.67   |  good  |  bad   |
  0x31	| 1,959,184  | 0.51 | 1.53 | 2.04 |  1.70   |  good  |  bad   |
  0x32	| 1,920,000  | 0.52	| 1.56 | 2.08 |  1.74   |  bad   |  bad   |
*/

#define RGB_USART1_BRR    (0x26)

uint32_t rgb_uart1_user_cr1 = 0;
uint32_t rgb_uart1_user_cr2 = 0;
uint32_t rgb_uart1_user_cr3 = 0;
uint32_t rgb_uart1_user_brr = 0;

void RGB_USART1_enable()
{
  rgb_uart1_user_brr = USART1->BRR;
  rgb_uart1_user_cr3 = USART1->CR3;
  rgb_uart1_user_cr2 = USART1->CR2;
  rgb_uart1_user_cr1 = USART1->CR1;

  USART1->CR1 = 0;                    /// disable USART
  USART1->BRR = RGB_USART1_BRR;
  USART1->CR3 = RGB_USART1_CR3;
  USART1->CR2 = RGB_USART1_CR2;
  USART1->CR1 = RGB_USART1_CR1;       /// enable USART1
}

void RGB_USART1_disable()
{
    USART1->CR1 = 0;                  /// disable USART
  USART1->BRR = rgb_uart1_user_brr;
  USART1->CR3 = rgb_uart1_user_cr3;
  USART1->CR2 = rgb_uart1_user_cr2;
  USART1->CR1 = rgb_uart1_user_cr1;   /// enable USART1
}

/**********************************************************************/
inline void RGB_Remap_enable()
{
  F030_GPIO_pinAF_select(GPIOA, RGB_LED_PIN, GPIO_AF_1);
}

inline void RGB_Remap_disable() {}

/**********************************************************************/
inline void RGB_GPIO_enable()
{
  F030_GPIO_pinMode_output(GPIOA, RGB_LED_PIN, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_RGB_LED_PIN);
}

inline void RGB_GPIO_disable()
{
  GPIOA->BRR = _BV(RGB_LED_PIN);   /// LOW level
  F030_GPIO_pinMode_output(GPIOA, RGB_LED_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_RGB_LED_PIN);
}

/**********************************************************************/
#ifdef RGB_MODE_DMA
  void RGB_DMA_enable()
  {
    RGB_DMA_backup();

    #ifdef RGB_MODE_DMA_CHANNEL_2
      BITMASK_CLEAR(SYSCFG->CFGR1, SYSCFG_DMARemap_USART1Tx);   /// DMA_USART1_Tx no remap
    #endif

    #ifdef RGB_MODE_DMA_CHANNEL_4
      BITMASK_SET(SYSCFG->CFGR1, SYSCFG_DMARemap_USART1Tx);     /// DMA_USART1_Tx remap
    #endif

    BITMASK_SET(USART1->CR3, USART_CR3_DMAT);     /// enable DMA transmitter

    RGB_DMA_CHANNEL->CNDTR = RGB_DMA_CNDTR;
    RGB_DMA_CHANNEL->CPAR  = RGB_DMA_CPAR;
    RGB_DMA_CHANNEL->CMAR  = RGB_DMA_CMAR;
    RGB_DMA_CHANNEL->CCR   = RGB_DMA_CCR;         /// enable DMA
  }

  void RGB_DMA_disable() {
    RGB_DMA_CHANNEL->CCR = 0;                     /// disable DMA
    BITMASK_CLEAR(USART1->CR3, USART_CR3_DMAT);   /// disable DMA transmitter

    RGB_DMA_restore();
  }
#else
  void RGB_DMA_enable()  {}
  void RGB_DMA_disable() {}
#endif  // RGB_MODE_DMA


/**********************************************************************/
#define INV_BYTE(x)    ((uint8_t)(~(x)))
const uint8_t RGB_usart_encode[8] = {
  //        1..----..0
  INV_BYTE(0b00100010),   // 0 0 0
  INV_BYTE(0b00100011),   // 0 0 1

  INV_BYTE(0b00111010),   // 0 1 0
  INV_BYTE(0b00111011),   // 0 1 1

  INV_BYTE(0b10100010),   // 1 0 0
  INV_BYTE(0b10100011),   // 1 0 1

  INV_BYTE(0b10111010),   // 1 1 0
  INV_BYTE(0b10111011),   // 1 1 1
};


#define GET_3BIT_CODE(x)  (((x) >> 21) & 0b111)
#define RGB_ADJ(color, brightness)   ((((uint32_t)(color)) * (brightness) + 128) >> 8)

uint32_t RGB_adjustBrightness(const uint8_t *rgb_data) {
  uint32_t r = RGB_ADJ(rgb_data[0], rgb_brightness);
  uint32_t g = RGB_ADJ(rgb_data[1], rgb_brightness);
  uint32_t b = RGB_ADJ(rgb_data[2], rgb_brightness);
  return ((g << 16) | (r << 8) | (b << 0));  // WS2812B format
}

/**********************************************************************/
inline void RGB_show_begin()
{
  RGB_USART1_enable();
  RGB_Remap_enable();
  RGB_GPIO_enable();
  RGB_DMA_enable();
}

inline void RGB_show_end()
{
  RGB_DMA_disable();
  RGB_GPIO_disable();
  RGB_Remap_disable();
  RGB_USART1_disable();
}

/**********************************************************************/
#ifdef RGB_MODE_DMA

  void RGB_write_dma_buff(const uint8_t *rgb_data, uint8_t *dma_buff)
  {
    uint32_t color24 = RGB_adjustBrightness(rgb_data);
    for (int i = 0; i < 8; i++)
    {
      dma_buff[i] = RGB_usart_encode[ GET_3BIT_CODE(color24) ];
      color24 <<= 3;
    }
  }

  __attribute__((always_inline)) static __INLINE void RGB_DMA_wait_event()
  {
    DMA1->IFCR = RGB_DMA_FLAG_HT | RGB_DMA_FLAG_TC;   /// clear flag
    DMA1->IFCR;                                       /// wait clear flag
    NVIC_ClearPendingIRQ(RGB_DMA_IRQ);
    do __WFE(); while ((DMA1->ISR & (RGB_DMA_FLAG_HT | RGB_DMA_FLAG_TC)) == 0);
  }

  void RGB_show_data(uint8_t *buff, int len)
  {
    RGB_write_dma_buff(&buff[0], rgb_dma_usart_buff);  /// encode led[0]

    RGB_show_begin();

    for (int i = 0; i < (len + 3); i += 6)
    {
      RGB_write_dma_buff(&buff[i + 3], rgb_dma_usart_buff + RGB_DMA_USART_BUFF_SIZE / 2);
      RGB_DMA_wait_event();

      RGB_write_dma_buff(&buff[i + 6], rgb_dma_usart_buff);
      RGB_DMA_wait_event();
    }

    RGB_show_end();
  }
#endif


#ifdef RGB_MODE_CLASSIC
  void RGB_show_data(uint8_t *buff, int len)
  {
    RGB_show_begin();

    for (int i = 0; i < len; i += 3)
    {
      uint32_t color24 = RGB_adjustBrightness(&buff[i]);
      for (int i = 0; i < 8; i++)
      {
        while ((USART1->ISR & USART_FLAG_TXE) == 0);
        USART1->TDR = RGB_usart_encode[ GET_3BIT_CODE(color24) ];
        color24 <<= 3;
      }
    }
    while ((USART1->ISR & USART_FLAG_TC) == 0);   // wait usart tx complete

    RGB_show_end();
  }
#endif


/**********************************************************************/
void RGB_show() {
  RGB_show_data(rgb_data_buff, sizeof(rgb_data_buff));
}

void RGB_setLed(int led, uint32_t color) {
  int start = led * 3;
  rgb_data_buff[start + 0] = (color >> 16) & 0xFF;  // red
  rgb_data_buff[start + 1] = (color >>  8) & 0xFF;  // green
  rgb_data_buff[start + 2] = (color >>  0) & 0xFF;  // blue
}

void RGB_setLedAll(uint32_t color) {
  for (int led = 0; led < RGB_NUM_LEDS; led++)
    RGB_setLed(led, color);
}

void RGB_clear() {
  RGB_setLedAll(RGB_BLACK);
}

/**********************************************************************/
void RGB_begin()
{
  #ifdef RGB_MODE_DMA
    BITMASK_SET(SCB->SCR, SCB_SCR_SEVONPEND_Msk);    /// enable events
  #endif

  BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_USART1    /// enable USART1 clock
                          | RCC_APB2Periph_SYSCFG);  /// enable SYSCFG clock
  BITMASK_SET(RCC->AHBENR,  RCC_AHBPeriph_GPIOA      /// enable GPIO clock
                          | RCC_AHBPeriph_DMA1);	   /// enable DMA1 clock
}

/**********************************************************************/
