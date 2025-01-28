
#include "Core.h"
#include <stdio.h>

#include "math_qfplib.h"


/**********************************************************************/
#define LED_PIN         1
#define LED_PORT        GPIOA
#define LED_PIN_SPEED   GPIO_Speed_2MHz

#define LED_LOW()       BITMASK_SET(LED_PORT->BRR,  _BV(LED_PIN))
#define LED_HIGH()      BITMASK_SET(LED_PORT->BSRR, _BV(LED_PIN))
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
  /// Setup
  Core_begin();
  delay_ms(100);
  GPIO_begin();
  USART1_begin_A9A10(BAUD_1M);
  Core_PrintInfo();

  volatile float x = 0.24;
  volatile float y = 0.26;

  x += y;
  x -= y;
  x *= y;
  x /= y;

  sinf(x);
  cosf(x);
  tanf(x);
  atan2f(x, y);

  logf(x);
  expf(x);
  sqrtf(x);

  int i = x;
  unsigned int ui = y;
  float f1 = i;
  float f2 = ui;

  if (x > y)
    printf("GT: %d\n", qfp_fcmp(x, y));

  if (x < y)
    printf("LT: %d\n", qfp_fcmp(x, y));

  if (x == y)
    printf("EQ: %d\n", qfp_fcmp(x, y));


  /// Loop
  while (1)
  {
  }
}

/**********************************************************************/
