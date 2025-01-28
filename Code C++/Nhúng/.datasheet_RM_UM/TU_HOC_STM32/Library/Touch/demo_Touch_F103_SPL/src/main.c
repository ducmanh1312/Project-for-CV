
#include <stdio.h>
#include "Core.h"
#include "Touch_F103.h"

/**********************************************************************/
int main()
{
  Core_begin();
  delay(100);
	
  USART1_begin_A9A10(BAUD_1M);
  Core_PrintInfo();


  #define TOUCH_1  TOUCH_PIN_A0
  #define TOUCH_2  TOUCH_PIN_A6
  #define TOUCH_3  TOUCH_PIN_A3
  Touch_begin(_BV(TOUCH_1) | _BV(TOUCH_2) | _BV(TOUCH_3));


  while (1)
  {
    printf("-1500 4500 ");

    printf("%5d   ", Touch_read(TOUCH_1));
    printf("%5d   ", Touch_read(TOUCH_2));
    printf("%5d   ", Touch_read(TOUCH_3));
    printf("\t");

    printf("%5d   ", Touch_read_state(TOUCH_1));
    printf("%5d   ", Touch_read_state(TOUCH_2));
    printf("%5d   ", Touch_read_state(TOUCH_3));

    printf("\n");

    delay(20);
  } // end loop
} // end main

/**********************************************************************/
