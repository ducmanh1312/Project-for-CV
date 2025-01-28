// Kết nối Arduino với thNumber:
//    Arduino pin       thNumber pin
//       4        ---     SDI
//       5        ---     RCK
//       6        ---     SCK
//       VCC      ---     V3
//       GND      ---     GND
int thNumber_SDI_pin = 4;
int thNumber_SCK_pin = 5;
int thNumber_RCK_pin = 6;
#include <thNumber.h>


// Kết nối Arduino với thBuzzer:
//    Arduino pin       thBuzzer pin
//       2        ---    A2  (nối với chân A1 sẽ kêu to hơn)
//       GND      ---     B
int buzzer_pin = 2;


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

  pinMode(knob_sensor_pin, INPUT);  // cài đặt INPUT để đọc giá trị cảm biến
  pinMode(buzzer_pin, OUTPUT);      // cài đặt OUTPUT điều khiển buzzer
  thNumber.begin(thNumber_SDI_pin, thNumber_SCK_pin, thNumber_RCK_pin);  // cài đặt thNumber
}



// Hàm loop() chạy lặp lại vô hạn:
void loop() 
{ 
  // đọc giá trị cảm biến:
  int threshold = analogRead(knob_sensor_pin);  // giá trị ngưỡng biến trở
  int distance_cm = srf05.ping_cm();            // đo khoảng cách (đơn vị cm)


  // so sánh giá trị cảm biến: Nếu có vật cản thì loa kêu
  if (distance_cm < threshold)
  {
    tone(buzzer_pin, 440);  // phát tần số 440Hz
  }
  else
  {
    noTone(buzzer_pin);     // dừng phát
  }
 
  
  thNumber.setNum4(0, distance_cm);  // hiển thị giá trị khoảng cách lên thNumber
  
  
  // in kết quả ra màn hình:
  Serial.print(threshold);
  Serial.print("\t");
  Serial.println(distance_cm);
  
  
  delay(250);  // thời gian trễ giữa mỗi lần đọc
}

