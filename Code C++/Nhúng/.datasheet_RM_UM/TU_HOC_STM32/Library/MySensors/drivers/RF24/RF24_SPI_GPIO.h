#ifndef __RF24_SPI_GPIO_H__
#define __RF24_SPI_GPIO_H__

#include "basic.h"
C_DECLS_BEGIN

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


  #ifdef USART1_SYNC
      #define RF24_USART1_SCK_A4

      #define RF24_USART1_MISO_A3
    //#define RF24_USART1_MISO_A10

      #define RF24_USART1_MOSI_A2
    //#define RF24_USART1_MOSI_A9
    //#define RF24_USART1_MOSI_A14
  #endif

//#define RF24_MODE_DMA

  #ifdef RF24_MODE_DMA
    /// phải chọn kênh DMA khác với USART1_RX_MODE_DMA trong Core.h

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


/// Select the speed:
// SPI mode: clock = Clock_source / prescaler
#define RF24_SPI_BAUDRATE_PRESCALER   SPI_BaudRatePrescaler_16

// USART mode:
#define RF24_USART_BAUDRATE    1000000

/**********************************************************************/
/// Select the GPIO configuration:

#ifdef STM32F10X_MD
  #define RF24_CS_PORT             GPIOA
  #define RF24_CS_PIN              15

  #define RF24_CE_PORT             GPIOB
  #define RF24_CE_PIN              7

  #define RF24_IRQ_PORT            GPIOB
  #define RF24_IRQ_PIN             6
#endif


#ifdef STM32F0XX
  #define RF24_CE_PORT             GPIOF
  #define RF24_CE_PIN              0

  #define RF24_CS_PORT             GPIOF
  #define RF24_CS_PIN              1

  #define RF24_IRQ_PORT            GPIOA
  #define RF24_IRQ_PIN             4
#endif

/**********************************************************************/
void RF24_SPI_GPIO_begin();

uint8_t RF24_SPI_transfer(uint8_t data);

void RF24_ce(bool level);
void RF24_csn(bool level);
void RF24_wait_transmit_complete();
bool RF24_checkIRQ();

void RF24_transferBegin();
void RF24_transferEnd();

/**********************************************************************/
#ifdef STM32F10X_MD
  #if   RF24_IRQ_PIN < 5
    #define RF24_IRQ  (RF24_IRQ_PIN + 6)   // EXTI0_IRQn -> EXTI4_IRQn
  #elif RF24_IRQ_PIN < 10
    #define RF24_IRQ   EXTI9_5_IRQn
  #else
    #define RF24_IRQ   EXTI15_10_IRQn
  #endif
#endif


#ifdef STM32F0XX
  #if   RF24_IRQ_PIN < 2
    #define RF24_IRQ           EXTI0_1_IRQn
  #elif RF24_IRQ_PIN < 4
    #define RF24_IRQ           EXTI2_3_IRQn
  #else
    #define RF24_IRQ           EXTI4_15_IRQn
  #endif
#endif


#ifdef RF24_MODE_DMA

  #if   defined (RF24_TX_MODE_DMA_CHANNEL2)
    #define RF24_DMA_TX           DMA1_Channel2
  #elif defined (RF24_TX_MODE_DMA_CHANNEL3)
    #define RF24_DMA_TX           DMA1_Channel3
  #elif defined (RF24_TX_MODE_DMA_CHANNEL4)
    #define RF24_DMA_TX           DMA1_Channel4
  #endif

  #if   defined (RF24_RX_MODE_DMA_CHANNEL2)
    #define RF24_DMA_RX           DMA1_Channel2
    #define RF24_DMA_RX_TC_FLAG   DMA_ISR_TCIF2
    #define RF24_DMA_RX_IRQ       DMA1_Channel2_3_IRQn

  #elif defined (RF24_RX_MODE_DMA_CHANNEL3)
    #define RF24_DMA_RX           DMA1_Channel3
    #define RF24_DMA_RX_TC_FLAG   DMA_ISR_TCIF3
    #define RF24_DMA_RX_IRQ       DMA1_Channel2_3_IRQn

  #elif defined (RF24_RX_MODE_DMA_CHANNEL5)
    #define RF24_DMA_RX           DMA1_Channel5
    #define RF24_DMA_RX_TC_FLAG   DMA_ISR_TCIF5
    #define RF24_DMA_RX_IRQ       DMA1_Channel4_5_IRQn
  #endif

#endif

/**********************************************************************/
C_DECLS_END
#endif // __RF24_SPI_GPIO_H__
