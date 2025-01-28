int led = 2;
int light_sensor_pin = A3;

void setup() {
  Serial.begin(9600);  // khởi tạo kết nối tới máy tính với tốc độ 9600
  pinMode(light_sensor_pin, INPUT);  // cấu hình INPUT để đọc giá trị cảm biến

}

void loop() {
  int light_value = analogRead(light_sensor_pin);  // đọc giá trị cảm biến ánh sáng
  Serial.println(light_value);  // in kết quả ra màn hình
  delay(250);  // thời gian trễ giữa mỗi lần đọc

  
}
