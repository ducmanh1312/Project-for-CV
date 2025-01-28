// Kết nối Arduino với cảm biến nhiệt độ:
//    Arduino pin        thTemp pin
//       2         ---     OUT
//       VCC       ---     VCC
//       GND       ---     GND

int temperature_pin = 2;

#include <OneWire.h>            // https://github.com/PaulStoffregen/OneWire/archive/master.zip
#include <DallasTemperature.h>  // https://github.com/milesburton/Arduino-Temperature-Control-Library/archive/master.zip

OneWire  oneWire(temperature_pin);
DallasTemperature  sensors(&oneWire);


// Hàm setup() chạy một lần:
void setup()
{
  Serial.begin(9600);  // khởi tạo kết nối tới máy tính với tốc độ 9600
  sensors.begin();  // cài đặt cảm biến nhiệt độ
}


// Hàm loop() chạy lặp lại vô hạn:
void loop()
{ 
  sensors.requestTemperatures();                   // kích hoạt cảm biến nhiệt độ
  float temperature = sensors.getTempCByIndex(0);  // đọc giá trị nhiệt độ (C)
  Serial.println(temperature);                     // in kết quả ra màn hình
  delay(250);                                      // thời gian trễ giữa mỗi lần đọc
}