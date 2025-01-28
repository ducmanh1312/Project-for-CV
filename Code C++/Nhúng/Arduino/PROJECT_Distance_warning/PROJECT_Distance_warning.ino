int trigger_pin = 10;
int echo_pin = 11;
#include <NewPing.h>

// tạo 1 đối tượng cho của lớp NewPing bằng cách 
//truyền vào 2 tham số: chân Trigger (gửi tín hiệu siêu âm), chân Echo (nhận phản hồi)
NewPing srf05(trigger_pin,echo_pin); 

int thNumber_SDI_pin = 7;
int thNumber_SCK_pin = 8;
int thNumber_RCK_pin = 9;
#include <thNumber.h>

int knob_sensor_pin = A5;
int buzzer_pin = 12;

void setup() {
  Serial.begin(9600); 
  thNumber.begin(thNumber_SDI_pin, thNumber_SCK_pin, thNumber_RCK_pin);  
  pinMode(knob_sensor_pin, INPUT); // 
  pinMode(buzzer_pin, OUTPUT);
}

void loop() {
  // hàm analogRead đọc giá trị analog trả về từ chân biến trở, gán vào biến knob_sensor_pin
  int knob_value = analogRead(knob_sensor_pin);  
  // hàm ping_cm trả về giá trị khoảng cách đơn vị cm đến vật thể, gán vào biến distance_cm
  int distance_cm = srf05.ping_cm();             
  // hàm map chuyển đổi giá trị đọc khoảng cách 
  int threshold = map(knob_value,0,1023,0,500);  
  
  thNumber.setNum4(0, distance_cm);              // hàm setNum4 hiển thị giá trị distance_cm lên màn hình thNumber

  if( distance_cm < threshold)
  {
    // Hàm tone bật loa kêu ở tần số 500Hz
    tone(buzzer_pin, 500); 
    delay(200); // loa kêu trong 200ms
  }else
  {
    //Hàm notone tắt loa
    noTone(buzzer_pin);
  }

}
