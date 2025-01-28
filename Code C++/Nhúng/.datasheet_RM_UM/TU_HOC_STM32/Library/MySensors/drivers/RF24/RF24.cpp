/*
  The MySensors Arduino library handles the wireless radio link and protocol
  between your home built sensors/actuators and HA controller of choice.
  The sensors forms a self healing radio network with optional repeaters. Each
  repeater and gateway builds a routing tables in EEPROM which keeps track of the
  network topology allowing messages to be routed to nodes.

  Created by Henrik Ekblad <henrik.ekblad@mysensors.org>
  Copyright (C) 2013-2015 Sensnology AB
  Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors

  Documentation: http://www.mysensors.org
  Support Forum: http://forum.mysensors.org

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  version 2 as published by the Free Software Foundation.

  Based on maniacbug's RF24 library, copyright (C) 2011 J. Coliz <maniacbug@ymail.com>
  RF24 driver refactored and optimized for speed and size, copyright (C) 2016 Olivier Mauti <olivier@mysensors.org>
*/

/*************************************************************************/
#include <stdio.h>

#include "Core.h"
#include "RF24_SPI_GPIO.h"
#include "RF24.h"

#include "MyHwSTM32.h"  // chỉnh sửa: MY_CRITICAL_SECTION
#include "MyCustoms.h"


/*************************************************************************/
#define AUTO               (255u)
#define BROADCAST_ADDRESS  (255u)

/*************************************************************************/
//uint8_t MY_RF24_BASE_ADDR[MY_RF24_ADDR_WIDTH] = {MY_RF24_BASE_RADIO_ID};  // chỉnh sửa: ko sử dụng
uint8_t MY_RF24_NODE_ADDRESS = AUTO;

/*************************************************************************/
uint8_t my_rf24_config;
uint8_t my_rf24_channel;
uint8_t my_rf24_addrWidth;
uint8_t my_rf24_rf_setup;
uint8_t my_rf24_retries;
uint8_t my_rf24_base_addr[5];

/*************************************************************************/
void RF24_LoadConfig() {
  customRetryConfig();

  // load config:
  my_rf24_config    = RF->rf_config;
  my_rf24_channel   = RF->rf_channel;
  my_rf24_addrWidth = RF->rf_aw;
  my_rf24_retries   = RF->rf_retries;
  my_rf24_rf_setup  = RF->rf_setup;
  for (int i = 0; i < my_rf24_addrWidth; i++)
    my_rf24_base_addr[i] = RF->rf_addr[i];

  #ifndef MY_GATEWAY_SERIAL
    printf("%02X ", RF->rf_config);
    printf("%02X ", RF->rf_aw);
    printf("%02X ", RF->rf_retries);
    printf("%02X ", RF->rf_channel);
    printf("%02X ", RF->rf_setup);
    for (int i = 0; i < 5; i++)
      printf(" %02X", RF->rf_addr[i]);
    printf("\n");
  #endif
}


/*************************************************************************/
#if defined(MY_RX_MESSAGE_BUFFER_FEATURE)
  RF24_receiveCallbackType RF24_receiveCallback = NULL;
#endif


#ifdef LINUX_SPI_BCM
  uint8_t spi_rxbuff[32 + 1] ; //SPI receive buffer (payload max 32 bytes)
  uint8_t spi_txbuff[32 + 1] ; //SPI transmit buffer (payload max 32 bytes + 1 byte for the command)
#endif


/**********************************************************************/
uint8_t RF24_spiReadMultiByte(uint8_t cmd, uint8_t *buf, uint8_t len) {
  RF24_transferBegin();

  uint8_t *current = buf;
  uint8_t status = RF24_SPI_transfer(cmd);

  while (len--) {
    status = RF24_SPI_transfer(RF24_NOP);
    if (buf != NULL) *current++ = status;
  }

  RF24_transferEnd();
  return status;
}

/**********************************************************************/
uint8_t RF24_spiWriteMultiByte(uint8_t cmd, uint8_t *buf, uint8_t len) {
  RF24_transferBegin();

  uint8_t *current = buf;
  uint8_t status = RF24_SPI_transfer(cmd);

  while (len--)
    status = RF24_SPI_transfer(*current++);

  RF24_transferEnd();
  return status;
}

/**********************************************************************/
uint8_t RF24_spiByteTransfer(uint8_t cmd) {
	return RF24_spiWriteMultiByte(cmd, NULL, 0);
}

/**********************************************************************/
uint8_t RF24_RAW_readByteRegister(uint8_t cmd) {
	return RF24_spiReadMultiByte(cmd, NULL, 1);
}

uint8_t RF24_RAW_writeByteRegister(uint8_t cmd, uint8_t value) {
	return RF24_spiWriteMultiByte(cmd , &value, 1);
}

/**********************************************************************/
 void RF24_flushRX(void) {
//RF24_DEBUG(PSTR("RF24:flushRX\n"));
  RF24_spiByteTransfer(RF24_FLUSH_RX);
}

 void RF24_flushTX(void) {
//RF24_DEBUG(PSTR("RF24:flushTX\n"));
  RF24_spiByteTransfer(RF24_FLUSH_TX);
}

 uint8_t RF24_getStatus(void) {
  return RF24_spiByteTransfer(RF24_NOP);
}

 uint8_t RF24_getFIFOStatus(void) {
  return RF24_readByteRegister(RF24_FIFO_STATUS);
}

 void RF24_setChannel(const uint8_t channel) {
  RF24_writeByteRegister(RF24_RF_CH, channel);
}

 void RF24_setRetries(const uint8_t retransmitDelay, const uint8_t retransmitCount) {
  RF24_writeByteRegister(RF24_SETUP_RETR, retransmitDelay << RF24_ARD | retransmitCount << RF24_ARC);
}

void RF24_setRETR(const uint8_t retrValue) {
  RF24_writeByteRegister(RF24_SETUP_RETR, retrValue);
}

 void RF24_setAddressWidth(const uint8_t width) {
  RF24_writeByteRegister(RF24_SETUP_AW, width - 2);
}

 void RF24_setRFSetup(const uint8_t RFsetup) {
  RF24_writeByteRegister(RF24_RF_SETUP, RFsetup);
}

 void RF24_setFeature(const uint8_t feature) {
  RF24_writeByteRegister(RF24_FEATURE, feature);
}

 void RF24_setPipe(const uint8_t pipe) {
  RF24_writeByteRegister(RF24_EN_RXADDR, pipe);
}

 void RF24_setAutoACK(const uint8_t pipe) {
  RF24_writeByteRegister(RF24_EN_AA, pipe);
}

 void RF24_setDynamicPayload(const uint8_t pipe) {
  RF24_writeByteRegister(RF24_DYNPD, pipe);
}

 void RF24_setRFConfiguration(const uint8_t configuration) {
  RF24_writeByteRegister(RF24_NRF_CONFIG, configuration);
}

 void RF24_setPipeAddress(const uint8_t pipe, uint8_t* address, const uint8_t width) {
  RF24_writeMultiByteRegister(pipe, address, width);
}

 void RF24_setPipeLSB(const uint8_t pipe, const uint8_t LSB) {
  RF24_writeByteRegister(pipe, LSB);
}

 uint8_t RF24_getObserveTX(void) {
  return RF24_readByteRegister(RF24_OBSERVE_TX);
}

 void RF24_setStatus(const uint8_t status) {
  RF24_writeByteRegister(RF24_STATUS, status);
}

 void RF24_enableFeatures(void) {
  RF24_RAW_writeByteRegister(RF24_ACTIVATE, 0x73);
}

 void RF24_openWritingPipe(const uint8_t recipient) {
//RF24_DEBUG(PSTR("RF24:OPEN WPIPE,RCPT=%d\n"), recipient); // open writing pipe
  // only write LSB of RX0 and TX pipe
  RF24_setPipeLSB(RF24_RX_ADDR_P0, recipient);
  RF24_setPipeLSB(RF24_TX_ADDR, recipient);
}

 void RF24_startListening(void) {
//RF24_DEBUG(PSTR("RF24:STRT LIS\n"));	// start listening
  // toggle PRX
  RF24_setRFConfiguration(my_rf24_config | _BV(RF24_PWR_UP) | _BV(RF24_PRIM_RX) );
  // all RX pipe addresses must be unique, therefore skip if node ID is AUTO
  if (MY_RF24_NODE_ADDRESS != AUTO) {
    RF24_setPipeLSB(RF24_RX_ADDR_P0, MY_RF24_NODE_ADDRESS);
  }
  // start listening
  RF24_ce(HIGH);

  #ifdef MY_RX_MESSAGE_BUFFER_FEATURE
    NVIC_EnableIRQ(RF24_IRQ);         /// enable RF24_irqHandler
  #endif
}

 void RF24_stopListening(void) {
  #ifdef MY_RX_MESSAGE_BUFFER_FEATURE
    NVIC_DisableIRQ(RF24_IRQ);        /// disable RF24_irqHandler
  #endif

//RF24_DEBUG(PSTR("RF24:STP LIS\n"));	// stop listening
  RF24_ce(LOW);

  delayMicroseconds(130);  // timing
  RF24_setRFConfiguration(my_rf24_config | _BV(RF24_PWR_UP));
  delayMicroseconds(100);  // timing
}

 void RF24_powerDown(void) {
  RF24_ce(LOW);
  RF24_setRFConfiguration(my_rf24_config);
//RF24_DEBUG(PSTR("RF24:PD\n")); // power down
}

bool RF24_sendFailed = false;  // for main.cpp: thêm biến thông báo mất gói tin của lên truyền gần nhất

bool RF24_sendMessage(const uint8_t recipient, const void* buf, const uint8_t len)
{
  uint8_t RF24_status;

  RF24_stopListening();
  RF24_openWritingPipe( recipient );
//RF24_DEBUG(PSTR("RF24:SND:TO=%d,LEN=%d\n"), recipient, len);  // send message
  RF24_flushTX();  // flush TX FIFO

  // this command is affected in clones (e.g. Si24R1):  flipped NoACK bit when using W_TX_PAYLOAD_NO_ACK / W_TX_PAYLOAD
  // AutoACK is disabled on the broadcasting pipe - NO_ACK prevents resending
  RF24_spiWriteMultiByte(recipient == BROADCAST_ADDRESS ?
                         RF24_WRITE_TX_PAYLOAD_NO_ACK : RF24_WRITE_TX_PAYLOAD,
                        (uint8_t*)buf, len);

  RF24_ce(HIGH);  // go, TX starts after ~10us

  #ifdef MY_RX_MESSAGE_BUFFER_FEATURE
    RF24_wait_transmit_complete();
    RF24_status = RF24_getStatus();
  #else
    // timeout counter to detect HW issues
    uint16_t timeout = 0xFFFF;
    do {
      RF24_status = RF24_getStatus();
    } while (!(RF24_status & ( _BV(RF24_MAX_RT) | _BV(RF24_TX_DS) )) && timeout--);
    // timeout value after successful TX on 16Mhz AVR ~ 65500, i.e. msg is transmitted after ~36 loop cycles
  #endif

  RF24_ce(LOW);

  // reset interrupts
  RF24_setStatus(_BV(RF24_TX_DS) | _BV(RF24_MAX_RT) );
//  RF24_setStatus(_BV(RF24_TX_DS) | _BV(RF24_MAX_RT) | _BV(RF24_RX_DR));

  // Max retries exceeded
  if (RF24_status & _BV(RF24_MAX_RT)) {
    // flush packet
  //RF24_DEBUG(PSTR("!RF24:SND:MAX_RT\n"));	// max retries, no ACK
    RF24_flushTX();
    RF24_sendFailed = true;
  } else {
    RF24_sendFailed = false;
  }

  RF24_startListening();
  // true if message sent
  return (RF24_status & _BV(RF24_TX_DS));
}

 uint8_t RF24_getDynamicPayloadSize(void) {
//uint8_t result = RF24_spiMultiByteTransfer(RF24_READ_RX_PL_WID, NULL, 1, true);
  uint8_t result = RF24_spiReadMultiByte(RF24_READ_RX_PL_WID, NULL, 1);

  // check if payload size invalid
  if (result > 32) {
  //RF24_DEBUG(PSTR("!RF24:GDP:PAYL LEN INVALID=%d\n"), result); // payload len invalid
    RF24_flushRX();
    result = 0;
  }
  return result;
}

 bool RF24_isDataAvailable(void) {
  return (!(RF24_getFIFOStatus() & _BV(0)) );
}


uint8_t RF24_readMessage(void* buf) {
  const uint8_t len = RF24_getDynamicPayloadSize();
//RF24_DEBUG(PSTR("RF24:RDM:MSG LEN=%d\n"), len);

//RF24_spiMultiByteTransfer(RF24_READ_RX_PAYLOAD, (uint8_t*)buf, len, true);
  RF24_spiReadMultiByte(RF24_READ_RX_PAYLOAD, (uint8_t*)buf, len);

  // clear RX interrupt
  RF24_setStatus(_BV(RF24_RX_DR));
  return len;
}

void RF24_setNodeAddress(const uint8_t address) {
  if (address != AUTO) {
    MY_RF24_NODE_ADDRESS = address;
    // enable node pipe
    RF24_setPipe(_BV(RF24_ERX_P0 + RF24_BROADCAST_PIPE) | _BV(RF24_ERX_P0));
    // enable autoACK on pipe 0
    RF24_setAutoACK(_BV(RF24_ENAA_P0));
  }
}

uint8_t RF24_getNodeID(void) {
  return MY_RF24_NODE_ADDRESS;
}

bool RF24_sanityCheck(void) {
  // detect HW defect, configuration errors or interrupted SPI line, CE disconnect cannot be detected
  return (RF24_readByteRegister(RF24_RF_SETUP) == my_rf24_rf_setup) &
         (RF24_readByteRegister(RF24_RF_CH) == my_rf24_channel);
}


#if defined(MY_RX_MESSAGE_BUFFER_FEATURE)

void RF24_irqHandler()
{
  if (RF24_receiveCallback) {
    // Will stay for a while (several 100us) in this interrupt handler. Any interrupts from serial
    // rx coming in during our stay will not be handled and will cause characters to be lost.
    // As a workaround we re-enable interrupts to allow nested processing of other interrupts.
    // Our own handler is disconnected to prevent recursive calling of this handler.
#if defined(MY_GATEWAY_SERIAL) && !defined(__linux__)
//    detachInterrupt(digitalPinToInterrupt(MY_RF24_IRQ_PIN));
//    interrupts();

    // disable interrupt request
    BITMASK_CLEAR(EXTI->IMR, _BV(RF24_IRQ_PIN));
#endif
    // Read FIFO until empty.
    // Procedure acc. to datasheet (pg. 63):
    // 1.Read payload, 2.Clear RX_DR IRQ, 3.Read FIFO_status, 4.Repeat when more data available.
    // Datasheet (ch. 8.5) states, that the nRF de-asserts IRQ after reading STATUS.

    // Start checking if RX-FIFO is not empty, as we might end up here from an interrupt
    // for a message we've already read.
    while (RF24_isDataAvailable()) {
      RF24_receiveCallback();		// Must call RF24_readMessage(), which will clear RX_DR IRQ !
    }

    // Restore our interrupt handler.
#if defined(MY_GATEWAY_SERIAL) && !defined(__linux__)
//    noInterrupts();
//    attachInterrupt(digitalPinToInterrupt(MY_RF24_IRQ_PIN), RF24_irqHandler, FALLING);
    // enable interrupt request
    BITMASK_SET(EXTI->IMR, _BV(RF24_IRQ_PIN));
#endif
  } else {
    // clear RX interrupt
    RF24_setStatus(_BV(RF24_RX_DR));
  }

  EXTI->PR = _BV(RF24_IRQ_PIN);  // thêm lệnh xóa cờ: clear EXTI flag
}


void RF24_registerReceiveCallback(RF24_receiveCallbackType cb) {
  MY_CRITICAL_SECTION
  {
    RF24_receiveCallback = cb;
  }
}
#endif


/********************************************************************************/
void RF24_printDetails(void) {
  printf("\n");
  printf("RF_CONFIG   = 0x%02X\n", RF24_readByteRegister(RF24_NRF_CONFIG));
  printf("EN_AA       = 0x%02X\n", RF24_readByteRegister(RF24_EN_AA));
  printf("EN_RXADDR   = 0x%02X\n", RF24_readByteRegister(RF24_EN_RXADDR));
  printf("SETUP_AW    = 0x%02X\n", RF24_readByteRegister(RF24_SETUP_AW));
  printf("SETUP_RETR  = 0x%02X\n", RF24_readByteRegister(RF24_SETUP_RETR));
  printf("RF_CH       = %d\n"    , RF24_readByteRegister(RF24_RF_CH));
  printf("RF_SETUP    = 0x%02X\n", RF24_readByteRegister(RF24_RF_SETUP));
  printf("STATUS      = 0x%02X\n", RF24_readByteRegister(RF24_STATUS));
  printf("FIFO_STATUS = 0x%02X\n", RF24_readByteRegister(RF24_FIFO_STATUS));
  printf("DYNPD       = 0x%02X\n", RF24_readByteRegister(RF24_DYNPD));
  printf("FEATURE     = 0x%02X\n", RF24_readByteRegister(RF24_FEATURE));

  // RX payload width
  printf("RX_PW_P0-5  = %d%3d%3d%3d%3d%3d\n",
    RF24_readByteRegister(RF24_RX_PW_P0), RF24_readByteRegister(RF24_RX_PW_P1), RF24_readByteRegister(RF24_RX_PW_P2),
    RF24_readByteRegister(RF24_RX_PW_P3), RF24_readByteRegister(RF24_RX_PW_P4), RF24_readByteRegister(RF24_RX_PW_P5) );

  uint8_t buff[5];
  #define print_buff()  for (int i = sizeof(buff) - 1; i >= 0; i--) {printf(" %02X", buff[i]);} printf("\n");

  RF24_spiReadMultiByte(RF24_READ_REGISTER | RF24_TX_ADDR,    buff, sizeof(buff));
  printf("TX_ADDR     = 0x");
  print_buff();

  RF24_spiReadMultiByte(RF24_READ_REGISTER | RF24_RX_ADDR_P0, buff, sizeof(buff));
  printf("RX_ADDR_P0  = 0x");
  print_buff();

  RF24_spiReadMultiByte(RF24_READ_REGISTER | RF24_RX_ADDR_P1, buff, sizeof(buff));
  printf("RX_ADDR_P1  = 0x");
  print_buff();

  printf("RX_ADDR_P2  = 0x __ __ __ __ %02X\n", RF24_readByteRegister(RF24_RX_ADDR_P2));
  printf("RX_ADDR_P3  = 0x __ __ __ __ %02X\n", RF24_readByteRegister(RF24_RX_ADDR_P3));
  printf("RX_ADDR_P4  = 0x __ __ __ __ %02X\n", RF24_readByteRegister(RF24_RX_ADDR_P4));
  printf("RX_ADDR_P5  = 0x __ __ __ __ %02X\n", RF24_readByteRegister(RF24_RX_ADDR_P5));
}


/********************************************************************************/
bool RF24_initialize(void) {
  RF24_LoadConfig();

  // prevent warning
  (void)RF24_getObserveTX;

  // Initialize SPI & GPIO
  RF24_SPI_GPIO_begin();

#if defined(MY_RX_MESSAGE_BUFFER_FEATURE)
 //pinMode(MY_RF24_IRQ_PIN, INPUT);

  // assure SPI can be used from interrupt context
  // Note: ESP8266 & SoftSPI currently do not support interrupt usage for SPI,
  // therefore it is unsafe to use MY_RF24_IRQ_PIN with ESP8266/SoftSPI!
//  _SPI.usingInterrupt(digitalPinToInterrupt(MY_RF24_IRQ_PIN));
//  attachInterrupt(digitalPinToInterrupt(MY_RF24_IRQ_PIN), RF24_irqHandler, FALLING);

  #ifdef STM32F10X_MD
    F103_GPIO_pinMode_input(RF24_IRQ_PORT, RF24_IRQ_PIN, GPIO_Mode_IPU);
    F103_GPIO_external_interrupt_enable(RF24_IRQ_PORT, RF24_IRQ_PIN, EXTI_Trigger_Falling);
  #endif

  #ifdef STM32F0XX
    F030_GPIO_pinMode_input(RF24_IRQ_PORT, RF24_IRQ_PIN, GPIO_Mode_IN, GPIO_PuPd_UP);
    F030_GPIO_external_interrupt_enable(RF24_IRQ_PORT, RF24_IRQ_PIN, EXTI_Trigger_Falling);
  #endif
#endif

  // CRC and power up
  RF24_setRFConfiguration(my_rf24_config | _BV(RF24_PWR_UP)) ;
  // settle >2ms
  delay(5);
  // set address width
  RF24_setAddressWidth(my_rf24_addrWidth);

  // auto retransmit delay 1500us, auto retransmit count 15
//RF24_setRetries(RF24_SET_ARD, RF24_SET_ARC);
  RF24_setRETR(my_rf24_retries);

  // set channel
  RF24_setChannel(my_rf24_channel);
  // set data rate and pa level
  RF24_setRFSetup(my_rf24_rf_setup);
  // toggle features (necessary on some clones and non-P versions)
  RF24_enableFeatures();
  // enable ACK payload and dynamic payload
  RF24_setFeature(MY_RF24_FEATURE);
  // sanity check (this function is P/non-P independent)
  if (!RF24_sanityCheck()) {
  //RF24_DEBUG(PSTR("!RF24:INIT:SANCHK FAIL\n")); // sanity check failed, check wiring or replace module
    return false;
  }
  // enable broadcasting pipe
  RF24_setPipe(_BV(RF24_ERX_P0 + RF24_BROADCAST_PIPE));
  // disable AA on all pipes, activate when node pipe set
  RF24_setAutoACK(0x00);
  // enable dynamic payloads on used pipes
  RF24_setDynamicPayload(_BV(RF24_DPL_P0 + RF24_BROADCAST_PIPE) | _BV(RF24_DPL_P0));
  // listen to broadcast pipe
  my_rf24_base_addr[0] = BROADCAST_ADDRESS;
  RF24_setPipeAddress(RF24_RX_ADDR_P0 + RF24_BROADCAST_PIPE, (uint8_t*)&my_rf24_base_addr,
                      RF24_BROADCAST_PIPE > 1 ? 1 : my_rf24_addrWidth);
  // pipe 0, set full address, later only LSB is updated
  RF24_setPipeAddress(RF24_RX_ADDR_P0, (uint8_t*)&my_rf24_base_addr, my_rf24_addrWidth);
  RF24_setPipeAddress(RF24_TX_ADDR,    (uint8_t*)&my_rf24_base_addr, my_rf24_addrWidth);
  // reset FIFO
  RF24_flushRX();
  RF24_flushTX();
  // reset interrupts
  RF24_setStatus(_BV(RF24_TX_DS) | _BV(RF24_MAX_RT) | _BV(RF24_RX_DR));

  RF24_printDetails();
  return true;
}

/********************************************************************************/
