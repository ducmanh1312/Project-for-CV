// Kết nối Arduino với thBuzzer:
//    Arduino pin       thBuzzer pin
//       12        ---    A2  (nối với chân A1 sẽ kêu to hơn)
//       GND      ---     B

int buzzer_pin = 12;


// Hàm setup() chạy một lần:
void setup() 
{
  pinMode(buzzer_pin, OUTPUT);  // cài đặt OUTPUT điều khiển buzzer
}


// Hàm loop() chạy lặp lại vô hạn:
void loop() 
{
  tone(buzzer_pin, 440);   // phát tần số 440Hz trong 1000ms
  delay(1000);						 // thời gian phát
  noTone(buzzer_pin);      // dừng phát
  delay(1500);             // thời gian trễ

  tone(buzzer_pin, 4000);  // phát tần số 4000Hz trong 500ms
  delay(500);              // thời gian phát
  noTone(buzzer_pin);      // dừng phát
  delay(1000);             // thời gian trễ
}