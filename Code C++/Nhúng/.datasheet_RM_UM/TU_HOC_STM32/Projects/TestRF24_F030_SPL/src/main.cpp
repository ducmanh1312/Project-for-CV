
#include "Core.h"

#include <stdio.h>
#include <string.h>

#include "RF24.h"
#include "random.h"

/**********************************************************************/
#define LED_PIN         1
#define LED_PORT        GPIOA
#define LED_PIN_SPEED   GPIO_Speed_2MHz

#define LED_LOW()       LED_PORT->BRR  = _BV(LED_PIN)
#define LED_HIGH()      LED_PORT->BSRR = _BV(LED_PIN)
#define LED_TOGGLE()    BITMASK_TGL(LED_PORT->ODR, _BV(LED_PIN))

/**********************************************************************/
typedef struct {
  uint16_t uid;
  uint16_t counter;
  uint16_t rand;
} MSG;

MSG txData;

uint16_t interval;

/**********************************************************************/
void GPIO_begin() {
  // enable GPIO clock
  BITMASK_SET(RCC->AHBENR, RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB);

  F030_GPIO_pinMode_output(LED_PORT, LED_PIN, GPIO_Mode_OUT, GPIO_OType_PP, LED_PIN_SPEED);
  LED_HIGH();
}


/**********************************************************************/
void printName(uint16_t uid) {
  switch (uid) {
    case 0xE1CA: printf("n0"); break;
    case 0x4272: printf("n1"); break;
    case 0xD070: printf("n2"); break;
    default:     printf("??"); break;
  }
}

void printMsg(uint32_t time, const MSG &msg, const char *footer = "") {
  printf("%6d  ", time);
  printName(msg.uid);
  printf("  ");
  printf("[");
  printf("%04X", msg.uid);
  printf(" ");
  printf("%04X", msg.counter);
  printf(" ");
  printf("%5d", msg.rand);
  printf("]");
  printf("  %s", footer);
  printf("\n");
}


/**********************************************************************/
MSG rxData;
uint32_t rxTime = 0;

void RF24_RxCallBack() {
  rxTime = millis();
  RF24_readMessage(&rxData);
}

/**********************************************************************/
void RF24_begin() {
  RF24_initialize();
  RF24_setAutoACK(0x00);  // disable all Auto-ACK
  RF24_setRETR(0x00);     // disable auto retransmit delay & counter

  RF24_setFeature(0x00);  // disable all feature
  RF24_writeByteRegister(RF24_RX_PW_P1, sizeof(MSG));  // set rx msg width

  RF24_registerReceiveCallback( RF24_RxCallBack );
  RF24_printDetails();
}

/**********************************************************************/
void checkTx() {
  static uint32_t last_txTime = 0;
  uint32_t txTime = millis();

  if ((txTime - last_txTime) > interval) {
    last_txTime = txTime;

    interval = Rand_get12() + 4096;

    txData.rand = interval;
    txData.counter++;

    RF24_sendMessage(0xFF, &txData, sizeof(txData));
    printMsg(txTime, txData, "Tx");
    LED_TOGGLE();
  }
}

void checkRx() {
  static uint32_t last_rxTime = 0;

  if (rxTime != last_rxTime) {
    last_rxTime = rxTime;
    printMsg(last_rxTime, rxData);
  }
}

/**********************************************************************/
// main
/**********************************************************************/
int main(void) {
  /// Setup
  Core_HSIConfig();
//  Core_EraseOptionBytes();
  Core_begin();
  GPIO_begin();
  USART1_begin_A9A10(BAUD_1M);
  Core_PrintInfo();

  RF24_begin();

  txData.uid = Core_GetUid16();
//  switch (txData.uid) {
//    case 0xE1CA: interval = 4500; break;
//    case 0x4272: interval = 5000; break;
//    case 0xD070: interval = 5500; break;
//    default:     interval = 2000; break;
//  }

  Rand_begin(txData.uid);
  interval = Rand_get12() + 4096;


  /// Loop
  while (1) {
    checkTx();
    checkRx();
  }
}

/**********************************************************************/
