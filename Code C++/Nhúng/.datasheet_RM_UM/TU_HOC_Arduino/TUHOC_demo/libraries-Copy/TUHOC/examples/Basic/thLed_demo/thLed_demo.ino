// Kết nối Arduino với thLed:
//    Arduino pin       thLed pin
//       4        ---     SDI
//       5        ---     RCK
//       6        ---     SCK
//       VCC      ---     VCC
//       GND      ---     GND

int thLED_SDI_pin = 4;  
int thLED_RCK_pin = 5;  
int thLED_SCK_pin = 6; 

#include <thLed.h>


// Hàm setup() chạy một lần:
void setup()
{ 
  thLed.begin(thLED_SDI_pin, thLED_SCK_pin, thLED_RCK_pin);  // cài đặt thLed
}


// Hàm loop() chạy lặp lại vô hạn:
void loop()
{
  thLed.setLed(2, LED_ON);   // bật Led 2
  thLed.setLed(7, LED_ON);   // bật Led 7
  delay(500);                // thời gian led sáng
  
  thLed.setLed(2, LED_OFF);  // tắt Led 2
  thLed.setLed(7, LED_OFF);  // tắt Led 7
  delay(1500);               // thời gian led tối
}
