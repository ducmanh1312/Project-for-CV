
#include "Core.h"
#include <stdio.h>

#include "random.h"

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
// main
/**********************************************************************/
int main(void) {
  /// Setup
  Core_HSIConfig();
//Core_EraseOptionBytes();
  Core_begin();
  GPIO_begin();

  USART1_begin_A9A10(BAUD_1M);
  Core_PrintInfo();

  Rand_begin(Core_GetUid16());


  /// Loop
  while (1) {
    printf("%d\n", Rand_get16());
    LED_TOGGLE();
    delay_ms(1000);
  }
}

/**********************************************************************/
