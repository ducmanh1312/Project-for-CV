// Kết nối Arduino với thColorLed:
//    Arduino pin       thColorLed pin
//        9        ---     DIN
//       VCC       ---     VCC
//       GND       ---     GND

#include <FastLED.h>            // FastLED library - http://fastled.io

#define LED_PIN             9
#define NUM_LEDS         (5*1)  // total number of LEDs
#define GLOBAL_BRIGHTNESS  15   // Max brightness = 255 (very bright)


#define LED_UP     0            // Vị trí các LED trên module thColorLed
#define LED_RIGHT  1
#define LED_CENTER 2
#define LED_LEFT   3
#define LED_DOWN   4

CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(GLOBAL_BRIGHTNESS);
}

void loop()
{
  leds[LED_UP]     = CRGB::Red;
  leds[LED_LEFT]   = CRGB::Green;
  leds[LED_DOWN]   = CRGB::Blue;
  leds[LED_RIGHT]  = CRGB::Yellow;
  leds[LED_CENTER] = CRGB(255,255,255);   // or CRGB::White

  FastLED.show();     // Cập nhật hiển thị các Led
  delay(2500);


  leds[LED_UP]     = CRGB::Green;
  leds[LED_LEFT]   = CRGB::Blue;
  leds[LED_RIGHT]  = CRGB::Red;

  int hsv_saturation = 255;
  int hsv_value = 255;
  for (int hsv_hue = 0; hsv_hue < 256; hsv_hue++)
  {
    leds[LED_CENTER] = CHSV(hsv_hue, hsv_saturation, hsv_value);
    leds[LED_DOWN].setHue(hsv_hue + 128);

    FastLED.show();     // Cập nhật hiển thị các Led
    delay(20);
  }
}

