/*
* The MySensors Arduino library handles the wireless radio link and protocol
* between your home built sensors/actuators and HA controller of choice.
* The sensors forms a self healing radio network with optional repeaters. Each
* repeater and gateway builds a routing tables in EEPROM which keeps track of the
* network topology allowing messages to be routed to nodes.
*
* Created by Henrik Ekblad <henrik.ekblad@mysensors.org>
* Copyright (C) 2013-2016 Sensnology AB
* Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors
*
* Documentation: http://www.mysensors.org
* Support Forum: http://forum.mysensors.org
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* version 2 as published by the Free Software Foundation.
*
* Based on maniacbug's RF24 library, copyright (C) 2011 J. Coliz <maniacbug@ymail.com>
* RF24 driver refactored and optimized for speed and size, copyright (C) 2016 Olivier Mauti <olivier@mysensors.org>
*/

#ifndef __RF24_H__
#define __RF24_H__

#include "basic.h"
C_DECLS_BEGIN

// SPI settings
// #if !defined(MY_RF24_SPI_MAX_SPEED)
// // default 2Mhz - safe for nRF24L01+ clones
// #define MY_RF24_SPI_MAX_SPEED 8000000
// #endif
// #define MY_RF24_SPI_DATA_ORDER MSBFIRST
// #define MY_RF24_SPI_DATA_MODE SPI_MODE0

// #if defined (ARDUINO) && !defined (__arm__) && !defined (_SPI)
// #include <SPI.h>
// #if defined(MY_SOFTSPI)
// SoftSPI<MY_SOFT_SPI_MISO_PIN, MY_SOFT_SPI_MOSI_PIN, MY_SOFT_SPI_SCK_PIN, MY_RF24_SPI_DATA_MODE>
// _SPI;
// #else
// #define _SPI SPI
// #endif
// #else

// #if defined(__arm__) || defined(__linux__)
// #include <SPI.h>
// #else
// extern HardwareSPI SPI;
// #endif

// #if !defined(_SPI)
// #define _SPI SPI
// #endif
// #endif

// // verify RF24 IRQ defs
// #if defined(MY_RX_MESSAGE_BUFFER_FEATURE)
// #if !defined(MY_RF24_IRQ_PIN)
// #error Message buffering feature requires MY_RF24_IRQ_PIN to be defined!
// #endif
// // SoftSPI does not support usingInterrupt()
// #ifdef MY_SOFTSPI
// #error RF24 IRQ usage cannot be used with Soft SPI
// #endif
// // ESP8266 does not support usingInterrupt()
// #ifdef ARDUINO_ARCH_ESP8266
// #error RF24 IRQ usage cannot be used with ESP8266
// #endif
// #ifndef SPI_HAS_TRANSACTION
// #error RF24 IRQ usage requires transactional SPI support
// #endif
// #else
// #ifdef MY_RX_MESSAGE_BUFFER_SIZE
// #error Receive message buffering requires RF24 IRQ usage
// #endif
// #endif

#include "MyConfig.h"


//#if defined(MY_RX_MESSAGE_BUFFER_FEATURE)
//#define MY_RF24_CONFIGURATION (uint8_t)((RF24_CRC_16 << 2) | (1 << RF24_MASK_TX_DS) | (1 << RF24_MASK_MAX_RT))
//#else
  #define MY_RF24_CONFIGURATION (uint8_t)((RF24_CRC_16 << 2))
//#endif

//#define MY_RF24_FEATURE  (uint8_t)( _BV(RF24_EN_DPL) | _BV(RF24_EN_ACK_PAY) )
  #define MY_RF24_FEATURE  (uint8_t)( _BV(RF24_EN_DPL) )


//#define MY_RF24_RF_SETUP (uint8_t)( ((MY_RF24_DATARATE & 0b10) << 4) | ((MY_RF24_DATARATE & 0b01) << 3) | (MY_RF24_PA_LEVEL << 1) ) + 1 // +1 for Si24R1

  #define MY_RF24_RF_SETUP (uint8_t)( ((MY_RF24_DATARATE & 0b10) << 4) | ((MY_RF24_DATARATE & 0b01) << 3) | (MY_RF24_PA_LEVEL << 1) )


// pipes
#define RF24_BROADCAST_PIPE		(1)
#define RF24_NODE_PIPE			  (0)

// debug
#if defined(MY_DEBUG_VERBOSE_RF24)
  #define RF24_DEBUG(x,...) printf(x, ##__VA_ARGS__)
//#define RF24_DEBUG(x,...) debug(x,  ##__VA_ARGS__)
#else
  #define RF24_DEBUG(x,...)
#endif


// PA levels
#define RF24_PA_MIN		    (0)
#define RF24_PA_LOW		    (1)
#define RF24_PA_HIGH	    (2)
#define RF24_PA_MAX		    (3)

// data rate
#define RF24_1MBPS 		    (0)
#define RF24_2MBPS 		    (1)
#define RF24_250KBPS 	    (2)

// CRC
#define RF24_CRC_DISABLED	(0)
#define RF24_CRC_8			  (2)
#define RF24_CRC_16			  (3)

// auto retry delay
#define RF24_SET_ARD		  (15) //=4000us

// auto retry count
#define RF24_SET_ARC		  (4)


#define MY_RF24_RETRIES   (uint8_t)((RF24_SET_ARD << 4) | RF24_SET_ARC)


// nRF24L01(+) register definitions
#define RF24_NRF_CONFIG		(0x00)
#define RF24_EN_AA			  (0x01)
#define RF24_EN_RXADDR		(0x02)
#define RF24_SETUP_AW		  (0x03)
#define RF24_SETUP_RETR		(0x04)
#define RF24_RF_CH		    (0x05)
#define RF24_RF_SETUP		  (0x06)
#define RF24_STATUS			  (0x07)
#define RF24_OBSERVE_TX		(0x08)
#define RF24_CD				    (0x09)
#define RF24_RX_ADDR_P0		(0x0A)
#define RF24_RX_ADDR_P1		(0x0B)
#define RF24_RX_ADDR_P2		(0x0C)
#define RF24_RX_ADDR_P3		(0x0D)
#define RF24_RX_ADDR_P4		(0x0E)
#define RF24_RX_ADDR_P5		(0x0F)
#define RF24_TX_ADDR		  (0x10)
#define RF24_RX_PW_P0		  (0x11)
#define RF24_RX_PW_P1		  (0x12)
#define RF24_RX_PW_P2		  (0x13)
#define RF24_RX_PW_P3		  (0x14)
#define RF24_RX_PW_P4		  (0x15)
#define RF24_RX_PW_P5	    (0x16)
#define RF24_FIFO_STATUS	(0x17)
#define RF24_DYNPD			  (0x1C)
#define RF24_FEATURE		  (0x1D)

// instructions
#define RF24_READ_REGISTER				    (0x00)
#define RF24_RPD					           	(0x09)
#define RF24_WRITE_REGISTER			    	(0x20)
#define RF24_REGISTER_MASK				    (0x1F)
#define RF24_ACTIVATE			    		    (0x50)
#define RF24_READ_RX_PL_WID			    	(0x60)
#define RF24_READ_RX_PAYLOAD			    (0x61)
#define RF24_WRITE_TX_PAYLOAD			    (0xA0)
#define RF24_WRITE_ACK_PAYLOAD			  (0xA8)
#define RF24_WRITE_TX_PAYLOAD_NO_ACK	(0xB0)
#define RF24_FLUSH_TX					        (0xE1)
#define RF24_FLUSH_RX					        (0xE2)
#define RF24_REUSE_TX_PL				      (0xE3)
#define RF24_NOP						          (0xFF)

// bit mnemonics
#define RF24_MASK_RX_DR		(6)
#define RF24_MASK_TX_DS		(5)
#define RF24_MASK_MAX_RT	(4)
#define RF24_EN_CRC		    (3)
#define RF24_CRCO		      (2)
#define RF24_PWR_UP			  (1)
#define RF24_PRIM_RX		  (0)

// auto ACK
#define RF24_ENAA_P5		(5)
#define RF24_ENAA_P4		(4)
#define RF24_ENAA_P3		(3)
#define RF24_ENAA_P2		(2)
#define RF24_ENAA_P1		(1)
#define RF24_ENAA_P0		(0)

// rx pipe
#define RF24_ERX_P5			(5)
#define RF24_ERX_P4			(4)
#define RF24_ERX_P3			(3)
#define RF24_ERX_P2			(2)
#define RF24_ERX_P1			(1)
#define RF24_ERX_P0			(0)

// dynamic payload
#define RF24_DPL_P5			(5)
#define RF24_DPL_P4			(4)
#define RF24_DPL_P3			(3)
#define RF24_DPL_P2			(2)
#define RF24_DPL_P1			(1)
#define RF24_DPL_P0			(0)

#define RF24_AW			    (0)
#define RF24_ARD			  (4)
#define RF24_ARC			  (0)
#define RF24_PLL_LOCK		(4)
#define RF24_RF_DR			(3)
#define RF24_RF_PWR			(6)
#define RF24_RX_DR			(6)
#define RF24_TX_DS			(5)
#define RF24_MAX_RT			(4)
#define RF24_RX_P_NO		(1)
#define RF24_TX_FULL		(0)
#define RF24_PLOS_CNT		(4)
#define RF24_ARC_CNT		(0)
#define RF24_TX_REUSE		(6)
#define RF24_FIFO_FULL	(5)
#define RF24_TX_EMPTY		(4)
#define RF24_RX_FULL		(1)
#define RF24_RX_EMPTY		(0)

// features
#define RF24_EN_DPL			  (2)
#define RF24_EN_ACK_PAY		(1)
#define RF24_EN_DYN_ACK		(0)

#define RF24_LNA_HCURR		(0)
#define RF24_RF_DR_LOW		(5)
#define RF24_RF_DR_HIGH		(3)
#define RF24_RF_PWR_LOW		(1)
#define RF24_RF_PWR_HIGH	(2)

// functions
//uint8_t RF24_spiMultiByteTransfer(const uint8_t cmd, uint8_t* buf, const uint8_t len, const bool aReadMode);
uint8_t RF24_spiReadMultiByte(uint8_t cmd, uint8_t *buf, uint8_t len);
uint8_t RF24_spiWriteMultiByte(uint8_t cmd, uint8_t *buf, uint8_t len);

uint8_t RF24_RAW_readByteRegister(const uint8_t cmd);
uint8_t RF24_RAW_writeByteRegister(const uint8_t cmd, const uint8_t value);

//#define RF24_readByteRegister(__reg)          RF24_RAW_readByteRegister(RF24_READ_REGISTER | (RF24_REGISTER_MASK & __reg))
//#define RF24_writeByteRegister(__reg,__value) RF24_RAW_writeByteRegister(RF24_WRITE_REGISTER | (RF24_REGISTER_MASK & __reg), __value)
//#define RF24_writeMultiByteRegister(__reg,__buf,__len) RF24_spiMultiByteTransfer(RF24_WRITE_REGISTER | (RF24_REGISTER_MASK & __reg),(uint8_t*)__buf, __len,false)
#define RF24_readByteRegister(reg)				         RF24_RAW_readByteRegister( RF24_READ_REGISTER  | (reg))
#define RF24_writeByteRegister(reg, value)         RF24_RAW_writeByteRegister(RF24_WRITE_REGISTER | (reg), value)
#define RF24_writeMultiByteRegister(reg, buf, len) RF24_spiWriteMultiByte(RF24_WRITE_REGISTER | (reg),(uint8_t*)buf, len)


void RF24_LoadConfig();

void RF24_flushRX(void);
void RF24_flushTX(void);
uint8_t RF24_getStatus(void);
uint8_t RF24_getFIFOStatus(void);
void RF24_openWritingPipe(const uint8_t recipient);
void RF24_startListening(void);
void RF24_stopListening(void);
void RF24_powerDown(void);

bool RF24_sendMessage(const uint8_t recipient, const void* buf, const uint8_t len);

uint8_t RF24_getDynamicPayloadSize(void);
bool RF24_isDataAvailable(void);

uint8_t RF24_readMessage(void* buf);

void RF24_setNodeAddress(const uint8_t address);
uint8_t RF24_getNodeID(void);
bool RF24_sanityCheck(void);
bool RF24_initialize(void);
void RF24_setChannel(const uint8_t channel);

void RF24_setRetries(const uint8_t retransmitDelay, const uint8_t retransmitCount);
void RF24_setRETR(const uint8_t retrValue);

void RF24_setAddressWidth(const uint8_t width);
void RF24_setRFSetup(const uint8_t RFsetup);
void RF24_setFeature(const uint8_t feature);
void RF24_setPipe(const uint8_t pipe);
void RF24_setAutoACK(const uint8_t pipe);
void RF24_setDynamicPayload(const uint8_t pipe);
void RF24_setRFConfiguration(const uint8_t configuration);
void RF24_setPipeAddress(const uint8_t pipe, uint8_t* address, const uint8_t width);
void RF24_setPipeLSB(const uint8_t pipe, const uint8_t LSB);
uint8_t RF24_getObserveTX(void);
void RF24_setStatus(const uint8_t status);
void RF24_enableFeatures(void);

void RF24_printDetails(void);
void RF24_SwitchConfig(void);

#if defined(MY_RX_MESSAGE_BUFFER_FEATURE)
typedef void (*RF24_receiveCallbackType)(void);
/**
 * Register a callback, which will be called (from interrupt context) for every message received.
 * @note When a callback is registered, it _must_ retrieve the message from the nRF24
 * by calling RF24_readMessage(). Otherwise the interrupt will not get deasserted
 * and message reception will stop.
 */
 void RF24_registerReceiveCallback(RF24_receiveCallbackType cb);


  #ifdef STM32F0XX
    #if   RF24_IRQ_PIN < 2
      #define RF24_irqHandler    EXTI0_1_IRQHandler
    #elif RF24_IRQ_PIN < 4
      #define RF24_irqHandler    EXTI2_3_IRQHandler
    #elif RF24_IRQ_PIN < 16
      #define RF24_irqHandler    EXTI4_15_IRQHandler
    #endif
  #endif

  #ifdef STM32F10X_MD
    #if   RF24_IRQ_PIN == 0
      #define RF24_irqHandler    EXTI0_IRQHandler
    #elif RF24_IRQ_PIN == 1
      #define RF24_irqHandler    EXTI1_IRQHandler
    #elif RF24_IRQ_PIN == 2
      #define RF24_irqHandler    EXTI2_IRQHandler
    #elif RF24_IRQ_PIN == 3
      #define RF24_irqHandler    EXTI3_IRQHandler
    #elif RF24_IRQ_PIN == 4
      #define RF24_irqHandler    EXTI4_IRQHandler
    #elif RF24_IRQ_PIN < 10
      #define RF24_irqHandler    EXTI9_5_IRQHandler
    #elif RF24_IRQ_PIN < 16
      #define RF24_irqHandler    EXTI15_10_IRQHandler
    #endif
  #endif

  void RF24_irqHandler();
#endif

/**********************************************************************/
C_DECLS_END
#endif // __RF24_H__
