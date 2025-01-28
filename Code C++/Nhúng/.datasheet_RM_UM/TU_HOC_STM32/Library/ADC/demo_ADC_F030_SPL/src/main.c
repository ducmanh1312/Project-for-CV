
#include <stdio.h>
#include "Core.h"
#include "ADC.h"

/**********************************************************************/
#define LED_PIN         1
#define LED_PORT        GPIOA
#define LED_PIN_SPEED   GPIO_Speed_2MHz

#define LED_LOW()       LED_PORT->BRR  = _BV(LED_PIN)
#define LED_HIGH()      LED_PORT->BSRR = _BV(LED_PIN)
#define LED_TOGGLE()    BITMASK_TOGGLE(LED_PORT->ODR, _BV(LED_PIN))

/**********************************************************************/
void GPIO_begin()
{
  // enable GPIO clock
  BITMASK_SET(RCC->AHBENR, RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB);

  F030_GPIO_pinMode_output(LED_PORT, LED_PIN, GPIO_Mode_OUT, GPIO_OType_PP, LED_PIN_SPEED);
}


/**********************************************************************/
// main
/**********************************************************************/
int main(void)
{
  /// Setup:
  Core_begin();

  USART1_begin_A9A10(BAUD_1M);
  Core_PrintInfo();

  GPIO_begin();

  F030_GPIO_pinMode_input(GPIOA, 0, GPIO_Mode_AN, GPIO_PuPd_NOPULL);

  ADC1_begin();


  /// Loop:
  while (1)
  {
    printf("%d\n", ADC1_read12(ADC_Channel_0, ADC_SampleTime_239_5Cycles));
    delay_ms(100);
    LED_TOGGLE();
  }
}

/**********************************************************************/


