
#include <stdio.h>
#include "Core.h"

#include "Serial.h"

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

  BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_GPIOB);            // enable GPIOB clock
  F103_GPIO_pinMode_output(LED_PORT, LED_PIN, GPIO_Mode_Out_PP | LED_PIN_SPEED);
}


/**********************************************************************/
int main(void)
{
  /// Setup:
  Core_begin();
  delay(100);

  Serial.begin(BAUD_1M);
  Core_PrintInfo();
  GPIO_begin();


  /// Loop:
  int x = 0;
  double y = -123456789.1234567;

  while (1)
  {
    if (Serial.available() > 0)
    {
      while (Serial.available() > 0)
      {
        Serial.print( (char)Serial.read() );
        delay_ms(1);
      }

      Serial.println();
      LED_TOGGLE();
    }

    Serial.print("counter = ");
    Serial.print(x, HEX);

    Serial.print("\t");
    Serial.println(y);

    x += 1;
    y += 0.01;

    LED_TOGGLE();
    delay(500);
  }
}
