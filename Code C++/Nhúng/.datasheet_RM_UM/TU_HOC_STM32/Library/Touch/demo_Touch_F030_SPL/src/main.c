
#include <stdio.h>
#include "Core.h"
#include "Touch_F030.h"


/**********************************************************************/
// main
/**********************************************************************/
int main(void)
{
  /// Setup:
  Core_begin();
  delay(100);
	
  USART1_begin_A9A10(BAUD_1M);
  Core_PrintInfo();


  #define TOUCH_1   TOUCH_PIN_A1
  #define TOUCH_2   TOUCH_PIN_A2
  #define TOUCH_3   TOUCH_PIN_A3
  Touch_begin( _BV(TOUCH_1) | _BV(TOUCH_2) | _BV(TOUCH_3) );

  /// Loop:
  while (1)
  {
    printf("-1500  5000  ");

    printf("%6d\t",  Touch_read(TOUCH_1));
    printf("%6d\t",  Touch_read(TOUCH_2));
    printf("%6d\t",  Touch_read(TOUCH_3));

    printf("\t");

    printf("%d\t",  Touch_read_state(TOUCH_1));
    printf("%d\t",  Touch_read_state(TOUCH_2));
    printf("%d\t",  Touch_read_state(TOUCH_3));

    printf("\n");
    delay(20);
  }
}

/**********************************************************************/
