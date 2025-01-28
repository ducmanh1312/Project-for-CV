#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

/**********************************************************************/
#include "basic.h"
C_DECLS_BEGIN

/*
    LSI   |  Watchdog          |   F    |     Step (ms)      |
   (Hz)   |  Prescaler         |  (Hz)  |   min   |   max    |
-------------------------------------------------------------|
          | IWDG_Prescaler_4   | 10,000 |   0.1   |    409.6 |
          | IWDG_Prescaler_8   |  5,000 |   0.2   |    819.2 |
          | IWDG_Prescaler_16  |  2,500 |   0.4   |  1,638.4 |
  40,000  | IWDG_Prescaler_32  |  1,250 |   0.8   |  3,276.8 |
          | IWDG_Prescaler_64  |    625 |   1.6   |  6,553.6 |
          | IWDG_Prescaler_128 |    313 |   3.2   | 13,107.2 |
          | IWDG_Prescaler_256 |    156 |   6.4   | 26,214.4 |
*/

bool Watchdog_hardware_begin();
void Watchdog_hardware_end();

void Watchdog_begin(int ms);
void Watchdog_reset();

void Watchdog_setPrescaler(uint8_t prescaler);

/**********************************************************************/
C_DECLS_END
#endif // __WATCHDOG_H__
