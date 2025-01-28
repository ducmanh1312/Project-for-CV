// Kết nối Arduino với thNumber:
//    Arduino pin       thNumber pin
//       7        ---     SDI
//       8        ---     SCK
//       9        ---     RCK
//       VCC      ---     VCC
//       GND      ---     GND

int thNumber_SDI_pin = 7;
int thNumber_SCK_pin = 8;
int thNumber_RCK_pin = 9;

#include <thNumber.h>


// Hàm setup() chạy một lần:
void setup()
{
  thNumber.begin(thNumber_SDI_pin, thNumber_SCK_pin, thNumber_RCK_pin);  // cài đặt thNumber
}


// Hàm loop() chạy lặp lại vô hạn:
void loop()
{
  for (int value = 0; value < 100; value++)
  {
    thNumber.setNum4(0, value);  // hiển thị giá trị value lên thNumber
    
    thNumber.showDot(0);         // bật hiển thị dấu chấm ở vị trí 0
    delay(500);
    thNumber.hideDot(0);				 // tắt hiển thị dấu chấm ở vị trí 0
    delay(500);
  }
}
