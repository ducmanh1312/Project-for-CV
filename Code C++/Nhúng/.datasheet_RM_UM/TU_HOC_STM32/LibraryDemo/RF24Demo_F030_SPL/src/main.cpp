
#include "Core.h"
#include <stdio.h>

#include "RF24.h"


/**********************************************************************/
#define LED_PIN         1
#define LED_PORT        GPIOA
#define LED_PIN_SPEED   GPIO_Speed_2MHz

#define LED_LOW()       LED_PORT->BRR  = _BV(LED_PIN)
#define LED_HIGH()      LED_PORT->BSRR = _BV(LED_PIN)
#define LED_TOGGLE()    BITMASK_TGL(LED_PORT->ODR, _BV(LED_PIN))

/**********************************************************************/
void GPIO_begin() {
  // enable GPIO clock
  BITMASK_SET(RCC->AHBENR, RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB);

  F030_GPIO_pinMode_output(LED_PORT, LED_PIN, GPIO_Mode_OUT, GPIO_OType_PP, LED_PIN_SPEED);
}


/**********************************************************************/
void RF24_RxCallBack() {
  uint8_t buff[32];
  uint8_t len = RF24_readMessage(buff);

  for (int i = 0; i < len; i++)
    printf("%02X ", buff[i]);
  printf("\n");
}


/**********************************************************************/
typedef struct {
  uint16_t uid;
  uint16_t counter;
} RF24_DATA;


RF24_DATA rf24_data;

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

  RF24_initialize();
  RF24_setAutoACK(0x00);  // disable all Auto-ACK
  RF24_setRETR(0x00);     // disable auto retransmit delay & counter

  RF24_registerReceiveCallback( RF24_RxCallBack );
  RF24_printDetails();


  rf24_data.uid = Core_GetUid16();


  /// Loop
  uint32_t prev_ms = 0;

  while (1) {
    uint32_t now_ms = millis();

    if ((now_ms - prev_ms) > 5000) {
      prev_ms = now_ms;

      uint8_t status = RF24_sendMessage(0xFF, &rf24_data, sizeof(rf24_data));
      //printf("%d\n", status);

      rf24_data.counter++;
      LED_TOGGLE();
    }
  }
}

/**********************************************************************/
