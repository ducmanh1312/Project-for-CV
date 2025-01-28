
#include <stdio.h>
#include "Core.h"

/**********************************************************************/
#include "DS18B20.h"

// kết nối DS18B20 với 2 chân A2 và A3 (3 chân chập vào nhau))
OneWireUSART ow;


/**********************************************************************/
#define LED_PIN         2
#define LED_PORT        GPIOB
#define LED_PIN_SPEED   GPIO_Speed_2MHz

#define LED_LOW()       BITMASK_SET(LED_PORT->BRR,  _BV(LED_PIN))
#define LED_HIGH()      BITMASK_SET(LED_PORT->BSRR, _BV(LED_PIN))
#define LED_TOGGLE()    BITMASK_TGL(LED_PORT->ODR,  _BV(LED_PIN))

/**********************************************************************/
void GPIO_begin() {
  BITMASK_SET(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);             // enable AFIO clock
  BITMASK_SET(AFIO->MAPR,   AFIO_MAPR_SWJ_CFG_JTAGDISABLE);  // disable JTAG: free A15

  BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_GPIOB);            // enable GPIOB clock
  F103_GPIO_pinMode_output(LED_PORT, LED_PIN, GPIO_Mode_Out_PP | LED_PIN_SPEED);
}


/**********************************************************************/
int main(void) {
  /// Setup
  Core_begin();
  delay_ms(10);

  USART1_begin_A9A10(BAUD_1M);
  Core_PrintInfo();
  GPIO_begin();


  ow_init(&ow);
  ow_search_reset(&ow);


  uint8_t id[8][8];
  int c = 0;

  while (ow_search(&ow, id[c]) == true) {
    /* Print device */
    printf("ID %d: ", c + 1);
    for (int i = 0; i < 8; i++)
      printf("%02X ", id[c][i]);
    printf("\n");

    c++;
  }

  printf("Search done!\r\n");


  /// Loop
  while (1) {
    if (c > 0) {
      float t;

      ds18x20_start(&ow, NULL);

      for (int i = 0; i < c; i++) {
        while (!ds18x20_read(&ow, id[i], &t));
        printf("Temp [%d] = %.2f\n", i, t);
      }
    }

    LED_TOGGLE();
    delay_ms(1000);
  }
}

/**********************************************************************/
