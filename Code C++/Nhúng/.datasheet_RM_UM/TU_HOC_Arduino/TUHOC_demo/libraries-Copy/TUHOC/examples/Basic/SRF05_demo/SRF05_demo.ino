// Kết nối Arduino với cảm biến SRF05:
//    Arduino pin        SRF05 pin
//       10        ---     TRIGGER
//       11        ---     ECHO
//       VCC       ---     VCC
//       GND       ---     GND

int TRIGGER_PIN = 10;
int ECHO_PIN    = 11;

#include <NewPing.h>  // https://bitbucket.org/teckel12/arduino-new-ping/downloads/NewPing_v1.8.zip
NewPing srf05(TRIGGER_PIN, ECHO_PIN);  // Cấu hình các pin


// Hàm setup() chạy một lần:
void setup() 
{
  Serial.begin(9600);  // khởi tạo kết nối tới máy tính với tốc độ 9600
}


// Hàm loop() chạy lặp lại vô hạn:
void loop() 
{
  int distance_cm = srf05.ping_cm();  // đo khoảng cách (đơn vị cm)
  Serial.println(distance_cm);  // in kết quả ra màn hình
  delay(250);  // thời gian trễ giữa mỗi lần đọc
}