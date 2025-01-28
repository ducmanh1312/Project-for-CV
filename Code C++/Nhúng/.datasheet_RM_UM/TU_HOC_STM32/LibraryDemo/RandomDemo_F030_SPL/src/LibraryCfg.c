
/**********************************************************************/
///                           CoreCfg                                ///
/**********************************************************************/


/**********************************************************************/
/// Select Options

//#define  CFG_CORE_CORETICK_SOURCE_DWT              /// not available on F0XX
//#define  CFG_CORE_CORETICK_SOURCE_SYSTICK_IRQ
  #define  CFG_CORE_CORETICK_SOURCE_SYSTICK

//#define  CFG_CORE_WAIT_MODE_CLASSIC                /// using classic method
  #define  CFG_CORE_WAIT_MODE_EVENTS                 /// using __WFE() and DMA


/**********************************************************************/
/// Clock and Flash latency settings

#ifdef STM32F10X_MD
  #define  CFG_Core_ClkFreq_MHz    (72UL)
  #define  CFG_Core_Flash_Latency  FLASH_Latency_1
#endif

#ifdef STM32F0XX
  #define  CFG_Core_ClkFreq_MHz    (48UL)
  #define  CFG_Core_Flash_Latency  FLASH_Latency_1
#endif


/**********************************************************************/
/// USART1

#define  CFG_CORE_USART1_TxPin   2
#define  CFG_CORE_USART1_RxPin   3

#define  CFG_CORE_USART1_RX_BUFF_SIZE  32

#ifdef CFG_CORE_WAIT_MODE_EVENTS
  //#define  CFG_CORE_USART1_TX_MODE_DMA_CHANNEL2    /// not available on F10X_MD
    #define  CFG_CORE_USART1_TX_MODE_DMA_CHANNEL4

  //#define  CFG_CORE_USART1_RX_MODE_DISABLE
  //#define  CFG_CORE_USART1_RX_MODE_DMA_CHANNEL3    /// not available on F10X_MD
    #define  CFG_CORE_USART1_RX_MODE_DMA_CHANNEL5

  //#define  CFG_CORE_DMA_BACKUP
#endif

#ifdef CFG_CORE_WAIT_MODE_CLASSIC
//#define  CFG_CORE_USART1_RX_MODE_DISABLE
  #define  CFG_CORE_USART1_RX_MODE_IRQ
#endif


/**********************************************************************/
#define  CFG_CORE
#include "Core.c.h"

/**********************************************************************/



/**********************************************************************/
///                             RF24Cfg                              ///
/**********************************************************************/


/**********************************************************************/
/// Select the communication: can be one of the following options

#if defined (STM32F10X_MD)
                              //  SCK    |  MISO   |  MOSI   | Clock_source (MHz) | Max baudrate (MHz)
//#define SPI1_DEFAULT        //  PA.5   |  PA.6   |  PA.7   |    72 (RCC_APB2)   |    36
  #define SPI1_REMAP          //  PB.3   |  PB.4   |  PB.5   |    72 (RCC_APB2)   |    36
//#define SPI2_DEFAULT        //  PB.13  |  PB.14  |  PB.15  |    36 (RCC_APB1)   |    18

//#define UART1_SYNC_DEFAULT  //  PA.8   |  PA.10  |  PA.9   |    72 (RCC_APB2)   |    4.5
//#define UART1_SYNC_REMAP    //  PA.8   |  PB.7   |  PB.6   |    72 (RCC_APB2)   |    4.5
//#define UART2_SYNC_DEFAULT  //  PA.4   |  PA.3   |  PA.2   |    36 (RCC_APB1)   |    2.25
//#define UART3_SYNC_DEFAULT  //  PB.12  |  PB.11  |  PB.10  |    36 (RCC_APB1)   |    2.25

#elif defined (STM32F0XX)
                              //  SCK    |  MISO   |  MOSI   | Clock_source (MHz) | Max baudrate (MHz)
  #define SPI1_DEFAULT        //  PA.5   |  PA.6   |  PA.7   |    48 (RCC_APB2)   |    24
//#define USART1_SYNC         //  PA.4   | PA.3/10 |PA.2/9/14|    48 (RCC_APB2)   |    6

  // SPI clock = Clock_source / prescaler
  #define RF24_SPI_BAUDRATE_PRESCALER   SPI_BaudRatePrescaler_8

  #ifdef USART1_SYNC
      #define RF24_USART_BAUDRATE    1000000

      #define RF24_USART1_SCK_A4

      #define RF24_USART1_MISO_A3
    //#define RF24_USART1_MISO_A10

      #define RF24_USART1_MOSI_A2
    //#define RF24_USART1_MOSI_A9
    //#define RF24_USART1_MOSI_A14
  #endif

//#define RF24_MODE_DMA

  #ifdef RF24_MODE_DMA
    // phải chọn kênh DMA khác với CFG_CORE_USART1_RX_MODE_DMA_CHANNEL
    #ifdef SPI1_DEFAULT
        #define RF24_TX_MODE_DMA_CHANNEL3
        #define RF24_RX_MODE_DMA_CHANNEL2
    #endif

    #ifdef USART1_SYNC
        #define RF24_TX_MODE_DMA_CHANNEL2
      //#define RF24_TX_MODE_DMA_CHANNEL4

        #define RF24_RX_MODE_DMA_CHANNEL3
      //#define RF24_RX_MODE_DMA_CHANNEL5
    #endif

    //#define RF24_DMA_BACKUP
  #endif

#endif


/**********************************************************************/
/// Select the GPIO configuration:

#define RF24_CE_PORT             GPIOF
#define RF24_CE_PIN              0

#define RF24_CS_PORT             GPIOF
#define RF24_CS_PIN              1

#define RF24_IRQ_PORT            GPIOA
#define RF24_IRQ_PIN             4

#define RF24_GPIO_Speed          GPIO_Speed_10MHz


/**********************************************************************/
//#define  CFG_RF24
//#include "RF24_SPI_GPIO.c.h"

/**********************************************************************/
