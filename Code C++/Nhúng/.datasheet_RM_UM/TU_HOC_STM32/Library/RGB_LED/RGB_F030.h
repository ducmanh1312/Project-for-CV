#ifndef __RGB_H__
#define __RGB_H__

#include "basic.h"

C_DECLS_BEGIN

/**********************************************************************/
/// Number of leds:
#define RGB_NUM_LEDS    15

/// Select led pin: (phải khác USART1_TxPin trong thư viện Core)
  #define RGB_LED_PIN_A2
//#define RGB_LED_PIN_A9
//#define RGB_LED_PIN_A14


/// Select using DMA:
  #define RGB_MODE_CLASSIC
//#define RGB_MODE_DMA_CHANNEL_2
//#define RGB_MODE_DMA_CHANNEL_4

//#define RGB_DMA_BACKUP

/**********************************************************************/
void RGB_begin();

void RGB_setBrightness(uint32_t brightness);
uint32_t RGB_getBrightness();

void RGB_setLed(int led, uint32_t color);
void RGB_setLedAll(uint32_t color);
void RGB_clear();
void RGB_show();
void RGB_show_data(uint8_t *buff, int len);

/**********************************************************************/
#define RGB_RED     0xFF0000
#define RGB_GREEN   0x00FF00
#define RGB_BLUE    0x0000FF

#define RGB_WHITE   0xFFFFFF
#define RGB_BLACK   0x000000
#define RGB_YELLOW  0xFFFF00
#define RGB_CYAN    0x00FFFF
#define RGB_PINK    0xFF00FF

/**********************************************************************/
C_DECLS_END
#endif // __RGB_H__

