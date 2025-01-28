// Kết nối Arduino với cảm biến ánh sáng:
//    Arduino pin       thLight pin
//       A5        ---     OUT
//       VCC       ---     V3
//       GND       ---     GND
int light_sensor_pin = A5;


// Kết nối Arduino với thLed:
//    Arduino pin       thLed pin
//       4        ---     SDI
//       5        ---     RCK
//       6        ---     SCK
//       VCC      ---     V3
//       GND      ---     GND
int thLED_SDI_pin = 4;
int thLED_RCK_pin = 5;
int thLED_SCK_pin = 6;
#include <thLed.h>


// Kết nối Arduino với biến trở:
//    Arduino pin       thKnob pin
//       A0        ---     VAR
//       VCC       ---     A
//       GND       ---     B
int knob_sensor_pin = A0;


// Kết nối Arduino với cảm biến SRF05:
//    Arduino pin        SRF05 pin
//       10        ---     TRIGGER
//       11        ---     ECHO
//       VCC       ---     VCC
//       GND       ---     GND
int TRIGGER_PIN = 10;
int ECHO_PIN    = 11;
#include <NewPing.h>  // https://bitbucket.org/teckel12/arduino-new-ping/downloads/NewPing_v1.8.zip
NewPing srf05(TRIGGER_PIN, ECHO_PIN);  // Cấu hình các pin SRF05



// Hàm setup() chạy một lần:
void setup() 
{
  Serial.begin(9600);  // khởi tạo kết nối tới máy tính với tốc độ 9600
  
  // cấu hình INPUT để đọc giá trị cảm biến:
  pinMode(knob_sensor_pin, INPUT);
  pinMode(light_sensor_pin, INPUT);
  
  thLed.begin(thLED_SDI_pin, thLED_SCK_pin, thLED_RCK_pin);  // cài đặt thLed
}



// Hàm loop() chạy lặp lại vô hạn:
void loop() 
{ 
  // đọc giá trị cảm biến:
  int threshold = analogRead(knob_sensor_pin);     // giá trị ngưỡng biến trở
  int light_value = analogRead(light_sensor_pin);  // giá trị cảm biến ánh sáng
  int distance_cm = srf05.ping_cm();               // đo khoảng cách (đơn vị cm)


  // so sánh giá trị cảm biến: Nếu trời tối hoặc có vật cản thì đèn sáng
  if ( (light_value > threshold) || (distance_cm < 50) )
  {
    thLed.setLed(0, LED_ON);  // bật Led 0
    thLed.setLed(5, LED_ON);  // bật Led 5
  }
  else
  {
    thLed.setLed(0, LED_OFF);   // tắt Led 0
    thLed.setLed(5, LED_OFF);   // tắt Led 5
  }
  
  
  // in kết quả ra màn hình:
  Serial.print(threshold);
  Serial.print("\t");
  Serial.print(light_value);
  Serial.print("\t");
  Serial.println(distance_cm);
  
  
  delay(250);  // thời gian trễ giữa mỗi lần đọc
}

