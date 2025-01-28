// Kết nối Arduino với biến trở:
//    Arduino pin       thKnob pin
//       A3        ---     VAR
//       VCC       ---     A
//       GND       ---     B

int knob_sensor_pin = A3;


// Hàm setup() chạy một lần:
void setup() 
{
  Serial.begin(9600);  // khởi tạo kết nối tới máy tính với tốc độ 9600
  pinMode(knob_sensor_pin, INPUT);  // cấu hình INPUT để đọc giá trị cảm biến
}


// Hàm loop() chạy lặp lại vô hạn:
void loop() 
{
  int knob_value = analogRead(knob_sensor_pin);  // đọc giá trị cảm biến
  Serial.println(knob_value);                    // in kết quả ra màn hình
  delay(250);                                    // thời gian trễ giữa mỗi lần đọc
}