#include "Core.h"
#include "RF24_SPI_GPIO.h"

#include "RF24.h"

#define RF24_GPIO_Speed   GPIO_Speed_10MHz

/**********************************************************************/
void RF24_csn(bool level) {
	GPIO_WriteBit(RF24_CS_PORT, _BV(RF24_CS_PIN), level);
}

void RF24_ce(bool level) {
	GPIO_WriteBit(RF24_CE_PORT, _BV(RF24_CE_PIN), level);
}

bool RF24_checkIRQ() {
  return GPIO_ReadInputDataBit(RF24_IRQ_PORT, _BV(RF24_IRQ_PIN));
}

/**********************************************************************/
#define RF24_RX_DR			(6)
#define RF24_TX_DS			(5)
#define RF24_MAX_RT			(4)

void RF24_wait_transmit_complete()
{
  /*-------------------------------------*
  timeout_start_ms(50);
  while (timeout_is_busy())
  {
    if ((EXTI->PR & _BV(RF24_IRQ_PIN)) != 0)
    {
      EXTI->PR = _BV(RF24_IRQ_PIN);     /// clear EXTI flag
      NVIC_ClearPendingIRQ(RF24_IRQ);   /// clear NVIC flag
      break;
    }
  }
  timeout_end();
  /*-------------------------------------*
  while ((RF24_getStatus() & (_BV(RF24_MAX_RT) | _BV(RF24_TX_DS))) == 0)
  {
    EXTI->PR = _BV(RF24_IRQ_PIN);    // clear EXTI flag
    EXTI->PR;
    NVIC_ClearPendingIRQ(RF24_IRQ);  // clear NVIC flag
    do __WFE(); while ((EXTI->PR & _BV(RF24_IRQ_PIN)) == 0);
  }

  /*-------------------------------------*/
	if ((RF24_getStatus() & (_BV(RF24_MAX_RT) | _BV(RF24_TX_DS))) == 0)
	{
		timeout_start_ms(100);  // max timeout = 16 * 4ms

		while (timeout_is_busy())
		{
			if ((EXTI->PR & _BV(RF24_IRQ_PIN)) != 0)
			{
				EXTI->PR = _BV(RF24_IRQ_PIN);     /// clear EXTI flag
				NVIC_ClearPendingIRQ(RF24_IRQ);   /// clear NVIC flag

				if ((RF24_getStatus() & (_BV(RF24_MAX_RT) | _BV(RF24_TX_DS))) != 0)
          break;
			}
		}

		timeout_end();
	}
	/*-------------------------------------*/

} // end function

/**********************************************************************/
#if defined (STM32F10X_MD)

  inline void RCC_enable_peripheral_clock(void *periph)
  {
    switch ((uint32_t)periph)
    {
      case ((uint32_t)SPI1):   BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_SPI1);   break;
      case ((uint32_t)SPI2):   BITMASK_SET(RCC->APB1ENR, RCC_APB1Periph_SPI2);   break;
      case ((uint32_t)USART1): BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_USART1); break;
      case ((uint32_t)USART2): BITMASK_SET(RCC->APB1ENR, RCC_APB1Periph_USART2); break;
      case ((uint32_t)USART3): BITMASK_SET(RCC->APB1ENR, RCC_APB1Periph_USART3); break;
    }
  }

  void RF24_GPIO_begin()
  {
    // enable clock GPIO
    RCC->APB2ENR |= F103_GPIO_get_rcc_clock_mask(RF24_CE_PORT)
                 |  F103_GPIO_get_rcc_clock_mask(RF24_CS_PORT)
                 |  F103_GPIO_get_rcc_clock_mask(RF24_IRQ_PORT);

    F103_GPIO_pinMode_output(RF24_CE_PORT, RF24_CE_PIN,  GPIO_Mode_Out_PP | RF24_GPIO_Speed);
    F103_GPIO_pinMode_output(RF24_CS_PORT, RF24_CS_PIN,  GPIO_Mode_Out_PP | RF24_GPIO_Speed);
    RF24_ce(LOW);
    RF24_csn(HIGH);
  }

  void RF24_SPI_begin()
  {
     #if defined SPI1_DEFAULT
        #define RF24_SPI               SPI1
        BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_GPIOA);
        F103_GPIO_pinMode_output(GPIOA, 5, GPIO_Mode_AF_PP | RF24_GPIO_Speed);
        F103_GPIO_pinMode_input( GPIOA, 6, GPIO_Mode_IPU);
        F103_GPIO_pinMode_output(GPIOA, 7, GPIO_Mode_AF_PP | RF24_GPIO_Speed);

    #elif defined SPI1_REMAP
        #define RF24_SPI               SPI1
        BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB);
        BITMASK_SET(AFIO->MAPR, GPIO_Remap_SPI1);
        F103_GPIO_pinMode_output(GPIOB, 3, GPIO_Mode_AF_PP | RF24_GPIO_Speed);
        F103_GPIO_pinMode_input( GPIOB, 4, GPIO_Mode_IPU);
        F103_GPIO_pinMode_output(GPIOB, 5, GPIO_Mode_AF_PP | RF24_GPIO_Speed);

    #elif defined SPI2_DEFAULT
        #define RF24_SPI               SPI2
        BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_GPIOB);
        F103_GPIO_pinMode_output(GPIOB, 13, GPIO_Mode_AF_PP | RF24_GPIO_Speed);
        F103_GPIO_pinMode_input( GPIOB, 14, GPIO_Mode_IPU);
        F103_GPIO_pinMode_output(GPIOB, 15, GPIO_Mode_AF_PP | RF24_GPIO_Speed);

    #elif defined (UART1_SYNC_DEFAULT)
        #define RF24_USART           USART1
        BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_GPIOA);
        F103_GPIO_pinMode_output(GPIOA,  8, GPIO_Mode_AF_PP | RF24_GPIO_Speed);
        F103_GPIO_pinMode_input( GPIOA,  9, GPIO_Mode_IPU);
        F103_GPIO_pinMode_output(GPIOA, 10, GPIO_Mode_AF_PP | RF24_GPIO_Speed);

    #elif defined UART1_SYNC_REMAP
        #define RF24_USART           USART1
        BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB);
        BITMASK_SET(AFIO->MAPR, GPIO_Remap_USART1);
        F103_GPIO_pinMode_output(GPIOA,  6, GPIO_Mode_AF_PP | RF24_GPIO_Speed);
        F103_GPIO_pinMode_input( GPIOA,  7, GPIO_Mode_IPU);
        F103_GPIO_pinMode_output(GPIOA,  8, GPIO_Mode_AF_PP | RF24_GPIO_Speed);

    #elif defined UART2_SYNC_DEFAULT
        #define RF24_USART           USART2
        BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_GPIOA);
        F103_GPIO_pinMode_output(GPIOA,  2, GPIO_Mode_AF_PP | RF24_GPIO_Speed);
        F103_GPIO_pinMode_input( GPIOA,  3, GPIO_Mode_IPU);
        F103_GPIO_pinMode_output(GPIOA,  4, GPIO_Mode_AF_PP | RF24_GPIO_Speed);

    #elif defined UART3_SYNC_DEFAULT
        #define RF24_USART           USART3
        BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_GPIOB);
        F103_GPIO_pinMode_output(GPIOB, 10, GPIO_Mode_AF_PP | RF24_GPIO_Speed);
        F103_GPIO_pinMode_input( GPIOB, 11, GPIO_Mode_IPU);
        F103_GPIO_pinMode_output(GPIOB, 12, GPIO_Mode_AF_PP | RF24_GPIO_Speed);
    #endif


    #ifdef RF24_SPI
      RCC_enable_peripheral_clock(RF24_SPI);  // enable clock SPI
      RF24_SPI->CR2 = 0;
      RF24_SPI->CR1 = SPI_CR1_SSM | SPI_CR1_SSI    // NSS Software mode
                    | RF24_SPI_BAUDRATE_PRESCALER  // SPI_clock = Clock_source / prescaler
                    | SPI_CR1_MSTR                 // Master mode
                    | SPI_CR1_SPE;                 // RF24_SPI enable
    #endif

    #ifdef RF24_USART
        RCC_enable_peripheral_clock(RF24_USART);

        RF24_USART->CR2 = USART_Clock_Enable
                        | USART_CPOL_Low
                        | USART_CPHA_1Edge
                        | USART_LastBit_Enable;

        USART_InitTypeDef USART_InitStructure;
        USART_InitStructure.USART_BaudRate   = RF24_USART_BAUDRATE;
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits   = USART_StopBits_1;
        USART_InitStructure.USART_Parity     = USART_Parity_No ;
        USART_InitStructure.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_Init(RF24_USART, &USART_InitStructure);

        BITMASK_SET(RF24_USART->CR1, USART_CR1_UE);  /// enable USART
    #endif
  } // end RF24_SPI_begin()


  #ifdef RF24_SPI
    uint8_t RF24_SPI_transfer(uint8_t data)
    {
      while ((RF24_SPI->SR & SPI_I2S_FLAG_TXE) == 0);
      RF24_SPI->DR = data;
      while ((RF24_SPI->SR & SPI_I2S_FLAG_RXNE) == 0);
      return (RF24_SPI->DR);
    }
  #endif

  #ifdef RF24_USART
    uint8_t __reverse(uint8_t x)
    {
      //  x = (((x & 0xAA) >> 1) | ((x & 0x55) << 1));
      //  x = (((x & 0xCC) >> 2) | ((x & 0x33) << 2));
      //  x = (((x & 0xF0) >> 4) | ((x & 0x0F) << 4));
      //  return x;
      return (__RBIT(x) >> 24);
    }

    uint8_t RF24_SPI_transfer(uint8_t data)
    {
      data = __reverse(data);
      while ((RF24_USART->SR & USART_FLAG_TXE) == 0);
      RF24_USART->DR = data;
      while ((RF24_USART->SR & USART_FLAG_RXNE) == 0);
      return __reverse(RF24_USART->DR);
    }
  #endif
#endif  // STM32F10X_MD


/**********************************************************************/
#ifdef STM32F0XX

  inline void RCC_enable_peripheral_clock(void *periph)
  {
    switch ((uint32_t)periph)
    {
      case ((uint32_t)SPI1):   BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_SPI1);   break;
      case ((uint32_t)USART1): BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_USART1); break;
    }
  }

  void RF24_GPIO_begin()
  {
    // enable GPIO clock
    BITMASK_SET(RCC->AHBENR, F030_GPIO_get_rcc_clock_mask(RF24_CE_PORT) |
                             F030_GPIO_get_rcc_clock_mask(RF24_CS_PORT) |
                             F030_GPIO_get_rcc_clock_mask(RF24_IRQ_PORT));

    F030_GPIO_pinMode_output(RF24_CE_PORT, RF24_CE_PIN,  GPIO_Mode_OUT, GPIO_OType_PP, RF24_GPIO_Speed);
    F030_GPIO_pinMode_output(RF24_CS_PORT, RF24_CS_PIN,  GPIO_Mode_OUT, GPIO_OType_PP, RF24_GPIO_Speed);
    RF24_ce(LOW);
    RF24_csn(HIGH);
  }

  #ifdef SPI1_DEFAULT

    #define RF24_SPI     SPI1

    void RF24_SPI_begin()
    {
      /// Configure SPI pins:
      BITMASK_SET(RCC->AHBENR, RCC_AHBPeriph_GPIOA);  // enable clock GPIOA
      F030_GPIO_pinAF_select(GPIOA, 5, GPIO_AF_0);
      F030_GPIO_pinAF_select(GPIOA, 6, GPIO_AF_0);
      F030_GPIO_pinAF_select(GPIOA, 7, GPIO_AF_0);
      F030_GPIO_pinMode_output(GPIOA, 5, GPIO_Mode_AF, GPIO_OType_PP, RF24_GPIO_Speed);
      F030_GPIO_pinMode_input( GPIOA, 6, GPIO_Mode_AF, GPIO_PuPd_UP);
      F030_GPIO_pinMode_output(GPIOA, 7, GPIO_Mode_AF, GPIO_OType_PP, RF24_GPIO_Speed);

      /// Configure RF24_SPI:
      RCC_enable_peripheral_clock(RF24_SPI);       // enable clock SPI
      RF24_SPI->CR2 = SPI_CR2_FRXTH                // FIFO reception threshold = 1/4
                    | SPI_DataSize_8b;             // data size
      RF24_SPI->CR1 = SPI_CR1_SSM                  // Software slave management
                    | SPI_CPOL_Low                 // CPOL = 0
                    | SPI_CPHA_1Edge               // CPHA = 0
                    | RF24_SPI_BAUDRATE_PRESCALER  // SPI_clock = Clock_source / prescaler
                    | SPI_Mode_Master              // master mode
                    | SPI_CR1_SPE;                 // SPI enable

      BITMASK_SET(RCC->AHBENR, RCC_AHBPeriph_DMA1);  // enable DMA1 clock
    }

    uint8_t RF24_SPI_transfer(uint8_t data)
    {
      while ((RF24_SPI->SR & SPI_I2S_FLAG_TXE) == 0);
      *(__IO uint8_t *) (&RF24_SPI->DR) = data;
      while ((RF24_SPI->SR & SPI_I2S_FLAG_RXNE) == 0);
      return *(__IO uint8_t *) (&RF24_SPI->DR);
    }
  #endif  // SPI1_DEFAULT


  #ifdef USART1_SYNC

    void RF24_SPI_begin()
    {
      #if   defined (RF24_USART1_SCK_A4)
        #define RF24_SCK_PIN       4
      #endif

      #if   defined (RF24_USART1_MISO_A3)
        #define RF24_MISO_PIN      3
      #elif defined (RF24_USART1_MISO_A10)
        #define RF24_MISO_PIN      10
      #endif

      #if   defined (RF24_USART1_MOSI_A2)
        #define RF24_MOSI_PIN      2
      #elif defined (RF24_USART1_MOSI_A9)
        #define RF24_MOSI_PIN      9
      #elif defined (RF24_USART1_MOSI_A14)
        #define RF24_MOSI_PIN      14
      #endif

      BITMASK_SET(RCC->AHBENR,  RCC_AHBPeriph_GPIOA);     /// enable GPIO clock
      BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_USART1);   /// enable USART1 clock
    }


    uint8_t RF24_SPI_transfer(uint8_t data)
    {
      while ((USART1->ISR & USART_FLAG_TXE) == 0);
      USART1->TDR = data;
      while ((USART1->ISR & USART_FLAG_RXNE) == 0);
      return USART1->RDR;
    }

    #define USART_DIV_SAMPLING8(__PCLK__, __BAUD__) ((((__PCLK__)*2U) + ((__BAUD__)/2U)) / (__BAUD__))

    #define RF24_USART1_SYNC_CR1  ( USART_WordLength_8b        \
                                  | USART_Parity_No            \
                                  | USART_Mode_Tx              \
                                  | USART_Mode_Rx              \
                                  | USART_CR1_OVER8            \
                                  | USART_CR1_UE )

    #define RF24_USART1_SYNC_CR2  ( USART_StopBits_1           \
                                  | USART_CR2_MSBFIRST         \
                                  | USART_CPOL_Low             \
                                  | USART_CPHA_1Edge           \
                                  | USART_LastBit_Enable       \
                                  | USART_Clock_Enable )

    #define RF24_USART1_SYNC_CR3  (USART_HardwareFlowControl_None)

    #define RF24_USART1_SYNC_BRR  (USART_DIV_SAMPLING8(Core_ClkFreq_MHz * 1e6, RF24_USART_BAUDRATE))

    uint32_t rf24_usart1_user_cr1 = 0;
    uint32_t rf24_usart1_user_cr2 = 0;
    uint32_t rf24_usart1_user_cr3 = 0;
    uint32_t rf24_usart1_user_brr = 0;
  #endif  // USART1_SYNC

#endif  // STM32F0XX


/**********************************************************************/
#ifdef STM32F0XX

  uint32_t rf24_dma_remap_backup;

  #ifdef RF24_DMA_BACKUP
    uint32_t rf24_dma_spi_tx_user_cpar;
    uint32_t rf24_dma_spi_tx_user_cmar;
    uint32_t rf24_dma_spi_tx_user_ccr;

    uint32_t rf24_dma_spi_rx_user_cpar;
    uint32_t rf24_dma_spi_rx_user_cmar;
    uint32_t rf24_dma_spi_rx_user_ccr;

    void RF24_DMA_backup()
    {
      rf24_dma_remap_backup = SYSCFG->CFGR1;

      rf24_dma_spi_rx_user_ccr  = DMA_SPI_RX->CCR;
      rf24_dma_spi_rx_user_cpar = DMA_SPI_RX->CPAR;
      rf24_dma_spi_rx_user_cmar = DMA_SPI_RX->CMAR;

      rf24_dma_spi_tx_user_ccr  = DMA_SPI_TX->CCR;
      rf24_dma_spi_tx_user_cpar = DMA_SPI_TX->CPAR;
      rf24_dma_spi_tx_user_cmar = DMA_SPI_TX->CMAR;
    }

    void RF24_DMA_restore() {
      DMA_SPI_RX->CCR  = rf24_dma_spi_rx_user_ccr;
      DMA_SPI_RX->CPAR = rf24_dma_spi_rx_user_cpar;
      DMA_SPI_RX->CMAR = rf24_dma_spi_rx_user_cmar;

      DMA_SPI_TX->CCR  = rf24_dma_spi_tx_user_ccr;
      DMA_SPI_TX->CPAR = rf24_dma_spi_tx_user_cpar;
      DMA_SPI_TX->CMAR = rf24_dma_spi_tx_user_cmar;

      SYSCFG->CFGR1 = rf24_dma_remap_backup;
    }

  #else
    void RF24_DMA_backup()
    {
      rf24_dma_remap_backup = SYSCFG->CFGR1;
    }

    void RF24_DMA_restore()
    {
      SYSCFG->CFGR1 = rf24_dma_remap_backup;
    }
  #endif  // RF24_DMA_BACKUP

#else
  void RF24_DMA_backup()  {}
  void RF24_DMA_restore() {}
#endif


/**********************************************************************/
#ifdef RF24_MODE_DMA

  #ifdef SPI1_DEFAULT
      #define RF24_DMA_TX_REG   SPI1->DR
      #define RF24_DMA_RX_REG   SPI1->DR
  #endif

  #ifdef USART1_SYNC
      #define RF24_DMA_TX_REG   USART1->TDR
      #define RF24_DMA_RX_REG   USART1->RDR
  #endif

  inline void RF24_DMA_enable()
  {
    RF24_DMA_backup();

    #ifdef RF24_TX_MODE_DMA_CHANNEL2
      BITMASK_CLEAR(SYSCFG->CFGR1, SYSCFG_DMARemap_USART1Tx);  /// DMA_USART1_Tx no remap
    #endif

    #ifdef RF24_TX_MODE_DMA_CHANNEL4
      BITMASK_SET(SYSCFG->CFGR1, SYSCFG_DMARemap_USART1Tx);    /// DMA_USART1_Tx remap
    #endif

    #ifdef RF24_RX_MODE_DMA_CHANNEL3
      BITMASK_CLEAR(SYSCFG->CFGR1, SYSCFG_DMARemap_USART1Rx);  /// DMA_USART1_Rx no remap
    #endif

    #ifdef RF24_RX_MODE_DMA_CHANNEL5
      BITMASK_SET(SYSCFG->CFGR1, SYSCFG_DMARemap_USART1Rx);    /// DMA_USART1_Rx remap
    #endif

    RF24_DMA_TX->CPAR  = (uint32_t)(&RF24_DMA_TX_REG);         /// peripheral address
    RF24_DMA_RX->CPAR  = (uint32_t)(&RF24_DMA_RX_REG);         /// peripheral address
  }

  inline void RF24_DMA_disable()
  {
    RF24_DMA_restore();
  }
#else
  void RF24_DMA_enable()  {}
  void RF24_DMA_disable() {}
#endif


/**********************************************************************/
#if defined (USART1_SYNC)
  static inline void RF24_USART_enable()
  {
    rf24_usart1_user_brr = USART1->BRR;
    rf24_usart1_user_cr3 = USART1->CR3;
    rf24_usart1_user_cr2 = USART1->CR2;
    rf24_usart1_user_cr1 = USART1->CR1;

    USART1->CR1 = 0;                      /// disable USART
    USART1->BRR = RF24_USART1_SYNC_BRR;
    USART1->CR3 = RF24_USART1_SYNC_CR3;
    USART1->CR2 = RF24_USART1_SYNC_CR2;
    USART1->CR1 = RF24_USART1_SYNC_CR1;   /// enable USART
  }

  static inline void RF24_USART_disable()
  {
    USART1->CR1 = 0;                      /// disable USART
    USART1->BRR = rf24_usart1_user_brr;
    USART1->CR3 = rf24_usart1_user_cr3;
    USART1->CR2 = rf24_usart1_user_cr2;
    USART1->CR1 = rf24_usart1_user_cr1;   /// enable USART
  }

  /**********************************************************************/
  inline void RF24_Remap_enable()
  {
  //F030_GPIO_pinMode_input(GPIOA, USART1_RxPin, GPIO_Mode_IN, GPIO_PuPd_UP);  /// disable USART1_RxPin
    F030_GPIO_pinAF_select(GPIOA, USART1_RxPin, GPIO_AF_7);

    F030_GPIO_pinAF_select(GPIOA, RF24_MISO_PIN, GPIO_AF_1);
    F030_GPIO_pinAF_select(GPIOA, RF24_MOSI_PIN, GPIO_AF_1);
    F030_GPIO_pinAF_select(GPIOA, RF24_SCK_PIN,  GPIO_AF_1);
  }

  inline void RF24_Remap_disable()
  {
  //F030_GPIO_pinMode_input(GPIOA, USART1_RxPin, GPIO_Mode_AF, GPIO_PuPd_UP);  /// enable USART1_RxPin
    F030_GPIO_pinAF_select(GPIOA, USART1_RxPin, GPIO_AF_1);
  }

  /**********************************************************************/
  inline void RF24_GPIO_enable()
  {
    F030_GPIO_pinMode_output(GPIOA, RF24_SCK_PIN,  GPIO_Mode_AF, GPIO_OType_PP, RF24_GPIO_Speed);  /// enable RF24_SCK_PIN
    F030_GPIO_pinMode_output(GPIOA, RF24_MOSI_PIN, GPIO_Mode_AF, GPIO_OType_PP, RF24_GPIO_Speed);  /// enable RF24_MOSI_PIN
    F030_GPIO_pinMode_input( GPIOA, RF24_MISO_PIN, GPIO_Mode_AF, GPIO_PuPd_UP);                    /// enable RF24_MISO_PIN
  }

  inline void RF24_GPIO_disable()
  {
    F030_GPIO_pinMode_input( GPIOA, RF24_MISO_PIN, GPIO_Mode_IN,  GPIO_PuPd_UP);                    /// disable RF24_MISO_PIN

    GPIOA->BRR = _BV(RF24_MOSI_PIN) | _BV(RF24_SCK_PIN);                                            /// LOW level
    F030_GPIO_pinMode_output(GPIOA, RF24_MOSI_PIN, GPIO_Mode_OUT, GPIO_OType_PP, RF24_GPIO_Speed);  /// disable RF24_MOSI_PIN
    F030_GPIO_pinMode_output(GPIOA, RF24_SCK_PIN,  GPIO_Mode_OUT, GPIO_OType_PP, RF24_GPIO_Speed);  /// disable RF24_SCK_PIN
  }

  /**********************************************************************/
  void RF24_transferBegin()
  {
    RF24_USART_enable();
    RF24_Remap_enable();
    RF24_GPIO_enable();
    RF24_DMA_enable();

    RF24_csn(LOW);
  }

  void RF24_transferEnd()
  {
  	RF24_csn(HIGH);

    RF24_DMA_disable();
    RF24_GPIO_disable();
    RF24_Remap_disable();
    RF24_USART_disable();
  }

#elif defined (SPI1_DEFAULT)
  void RF24_transferBegin()
  {
    RF24_DMA_enable();
    RF24_csn(LOW);
  }

  void RF24_transferEnd()
  {
    RF24_csn(HIGH);
    RF24_DMA_disable();
  }

#else
  void RF24_transferBegin()
  {
    RF24_csn(LOW);
  }

  void RF24_transferEnd()
  {
    RF24_csn(HIGH);
  }
#endif

/**********************************************************************/
void RF24_SPI_GPIO_begin() {
  RF24_GPIO_begin();
	RF24_SPI_begin();

  BITMASK_SET(SCB->SCR, SCB_SCR_SEVONPEND_Msk);         /// enable events

	#ifdef RF24_MODE_DMA
    BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_SYSCFG);   /// SYSCFG clock enabled
    BITMASK_SET(RCC->AHBENR, RCC_AHBPeriph_DMA1);       /// enable DMA1 clock
  #endif
}

/**********************************************************************/
