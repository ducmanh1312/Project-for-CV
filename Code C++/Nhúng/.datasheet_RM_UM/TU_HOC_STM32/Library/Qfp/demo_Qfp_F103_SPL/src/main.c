
#include <stdio.h>
#include "Core.h"

#include "math_qfplib.h"

/**********************************************************************/
#define LED_PIN         2
#define LED_PORT        GPIOB
#define LED_PIN_SPEED   GPIO_Speed_2MHz

#define LED_LOW()       BITMASK_SET(LED_PORT->BRR,  _BV(LED_PIN))
#define LED_HIGH()      BITMASK_SET(LED_PORT->BSRR, _BV(LED_PIN))
#define LED_TOGGLE()    BITMASK_TOGGLE(LED_PORT->ODR, _BV(LED_PIN))


/**********************************************************************/
void GPIO_begin()
{
  BITMASK_SET(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);             // enable AFIO clock
  BITMASK_SET(AFIO->MAPR,   AFIO_MAPR_SWJ_CFG_JTAGDISABLE);  // disable JTAG: free A15

  BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_GPIOB);           // enable GPIOB clock
  F103_GPIO_pinMode_output(LED_PORT, LED_PIN, GPIO_Mode_Out_PP | LED_PIN_SPEED);
}


/**********************************************************************/
int main(void)
{
  /// Setup
  Core_begin();
  delay_ms(100);

  USART1_begin_A9A10(BAUD_1M);
  Core_PrintInfo();
  GPIO_begin();


  volatile float x = -0.23;
  volatile float y = -0.26;

  x += y;
  x -= y;
  x *= y;
  x /= y;

  x = sinf(x);
  x = cosf(x);
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
    LED_TOGGLE();
    delay(1000);
  }
}

/**********************************************************************/
