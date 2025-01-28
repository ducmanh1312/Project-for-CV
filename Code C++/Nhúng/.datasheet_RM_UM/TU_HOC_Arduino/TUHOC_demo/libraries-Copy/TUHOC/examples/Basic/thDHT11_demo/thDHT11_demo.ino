// Kết nối Arduino với cảm biến DHT11:
//    Arduino pin       DHT11 pin
//       10       ---     OUT
//       VCC      ---     VCC
//       GND      ---     GND

int dht11_pin = 10;

#include <dht.h>  // https://arduino-info.wikispaces.com/file/view/DHT-lib.zip/545470280/DHT-lib.zip
dht  DHT;


// Hàm setup() chạy một lần:
void setup()
{
  Serial.begin(9600);  // khởi tạo kết nối tới máy tính với tốc độ 9600
  Serial.println("Humidity (%)\tTemperature (C)");
}


// Hàm loop() chạy lặp lại vô hạn:
void loop()
{
  DHT.read11(dht11_pin);  // kích hoạt cảm biến DHT11

  // in kết quả ra màn hình:
  Serial.print(DHT.humidity);       // độ ẩm (%)
  Serial.print("\t\t");
  Serial.println(DHT.temperature);  // nhiệt độ (C)

  delay(1000);  // thời gian trễ giữa mỗi lần đọc
}