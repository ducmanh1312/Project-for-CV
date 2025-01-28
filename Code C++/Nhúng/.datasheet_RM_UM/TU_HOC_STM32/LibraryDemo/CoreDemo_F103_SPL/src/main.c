
#include <stdio.h>
#include "Core.h"


/**********************************************************************/
#define LED_PIN         2
#define LED_PORT        GPIOB
#define LED_PIN_SPEED   GPIO_Speed_2MHz

#define LED_LOW()       LED_PORT->BRR  = _BV(LED_PIN)
#define LED_HIGH()      LED_PORT->BSRR = _BV(LED_PIN)
#define LED_TOGGLE()    BITMASK_TGL(LED_PORT->ODR, _BV(LED_PIN))

/**********************************************************************/
void GPIO_begin() {
  BITMASK_SET(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);             // enable AFIO clock
  BITMASK_SET(AFIO->MAPR,   AFIO_MAPR_SWJ_CFG_JTAGDISABLE);  // disable JTAG (free A15)

  BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_GPIOB);            // enable GPIOB clock
  F103_GPIO_pinMode_output(LED_PORT, LED_PIN, GPIO_Mode_Out_PP | LED_PIN_SPEED);
}


/**********************************************************************/
int main(void) {
  /// Setup
  Core_begin();
  delay_ms(100);

  USART1_begin_A9A10(BAUD_1M);
  Core_PrintInfo();

  GPIO_begin();


  /// Loop
  uint32_t delay_target = 0;
  while (1) {
    printf("%12u\t", micros());
    printf("%9u\t", millis());

//    printf("%u", SysTick24());
    printf("\n");

    LED_TOGGLE();
    delay_until_ms(delay_target += 100);
    LED_TOGGLE();

    if (USART1_available() > 0) {
      while (USART1_available() > 0) {
        printf("%c", USART1_read());
      }

      printf("\n");
      LED_TOGGLE();
    }

    //delay_ms(1000);
    delay_until_ms(delay_target += 900);
  }
}

/**********************************************************************/
