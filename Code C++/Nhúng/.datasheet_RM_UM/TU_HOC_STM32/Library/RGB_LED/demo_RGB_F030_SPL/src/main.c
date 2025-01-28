
#include <stdio.h>
#include "Core.h"
#include "RGB_F030.h"

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
void RGB_mix()
{
  for (int i = 0; i < RGB_NUM_LEDS; i += 5)
  {
    RGB_setLed(i + 0, RGB_RED);
    RGB_setLed(i + 1, RGB_GREEN);
    RGB_setLed(i + 2, RGB_CYAN);
    RGB_setLed(i + 3, RGB_PINK);
    RGB_setLed(i + 4, RGB_YELLOW);
  }
}

/**********************************************************************/
const uint8_t my_data[] = {
  0xFF, 0x00, 0x00,
  0x00, 0xFF, 0x00,
  0x00, 0x00, 0xFF,
  0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0x00,

  0xFF, 0x00, 0x00,
  0x00, 0xFF, 0x00,
  0x00, 0x00, 0xFF,
  0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0x00,

  0xFF, 0x00, 0x00,
  0x00, 0xFF, 0x00,
  0x00, 0x00, 0xFF,
  0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0x00,
};

/**********************************************************************/
// main
/**********************************************************************/
int main(void)
{
  /// Setup:
  Core_begin();
  delay_ms(100);
	
  USART1_begin_A9A10(BAUD_1M);
  Core_PrintInfo();

  GPIO_begin();

  RGB_begin();
  RGB_setBrightness(1);
	

  /// Loop:
  while (1)
  {
    #define T  1000

    printf("RED\n");
    RGB_setLedAll(RGB_RED);   RGB_show(); delay_ms(T);

    printf("GREEN\n");
    RGB_setLedAll(RGB_GREEN); RGB_show(); delay_ms(T);

    printf("BLUE\n");
    RGB_setLedAll(RGB_BLUE);   RGB_show(); delay_ms(T);

    printf("CYAN\n");
    RGB_setLedAll(RGB_CYAN);   RGB_show(); delay_ms(T);

    printf("WHITE\n");
    RGB_setLedAll(RGB_WHITE);  RGB_show(); delay_ms(T);

    printf("MIX\n");
		RGB_mix();                 RGB_show(); delay_ms(T);

    printf("USER_COLOR\n\n");
    RGB_show_data(my_data, sizeof(my_data)); delay_ms(T);
		
    delay_ms(T);
    LED_TOGGLE();
  }
}

/**********************************************************************/
