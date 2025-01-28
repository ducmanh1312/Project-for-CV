
#include <stdio.h>
#include "Core.h"
#include "ADC.h"

/**********************************************************************/
#define LED_PIN         2
#define LED_PORT        GPIOB
#define LED_PIN_SPEED   GPIO_Speed_2MHz

#define LED_LOW()       BITMASK_SET(LED_PORT->BRR,  _BV(LED_PIN))
#define LED_HIGH()      BITMASK_SET(LED_PORT->BSRR, _BV(LED_PIN))
#define LED_TOGGLE()    BITMASK_TOGGLE(LED_PORT->ODR, _BV(LED_PIN))

/**********************************************************************/
void GPIO_begin() {
  BITMASK_SET(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);             // enable AFIO clock
  BITMASK_SET(AFIO->MAPR,   AFIO_MAPR_SWJ_CFG_JTAGDISABLE);  // disable JTAG: free A15

  BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_GPIOB);           // enable GPIOB clock
  F103_GPIO_pinMode_output(LED_PORT, LED_PIN, GPIO_Mode_Out_PP | LED_PIN_SPEED);
}

/**********************************************************************/
int main(void) {
  /// Setup:
  Core_begin();
//  delay_ms(100);

  GPIO_begin();
  USART1_begin_A9A10(BAUD_1M);
  Core_PrintInfo();

  BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_GPIOA);    // enable GPIOA clock
  F103_GPIO_pinMode_input(GPIOA, 0, GPIO_Mode_AIN);

  ADC1_begin();


  /// Loop:
  while (1) {
    printf("%d\n", ADC1_read12(ADC_Channel_0, ADC_SampleTime_239_5Cycles));
    delay_ms(100);
    LED_TOGGLE();
  }
}

