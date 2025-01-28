// Kết nối Arduino với cảm biến ánh sáng:
//    Arduino pin       thLight pin
//       A3        ---     OUT
//       VCC       ---     V3
//       GND       ---     GND
int light_sensor_pin = A3;


// Kết nối Arduino với cảm biến DHT11:
//    Arduino pin       DHT11 pin
//       10       ---     OUT
//       VCC      ---     VCC
//       GND      ---     GND
int dht11_pin = 10;

#include <dht.h>  // https://arduino-info.wikispaces.com/file/view/DHT-lib.zip/545470280/DHT-lib.zip
dht  DHT;


// Kết nối Arduino với cảm biến nhiệt độ:
//    Arduino pin        thTemp pin
//       11        ---     OUT
//       VCC       ---     VCC
//       GND       ---     GND
int temperature_pin = 11;

#include <OneWire.h>            // https://github.com/PaulStoffregen/OneWire/archive/master.zip
#include <DallasTemperature.h>  // https://github.com/milesburton/Arduino-Temperature-Control-Library/archive/master.zip
OneWire  oneWire(temperature_pin);
DallasTemperature  sensors(&oneWire);


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


// Kết nối Arduino với nút bấm:
//    Arduino pin       thButton pin
//       9         ---     B1
//       8         ---     B2
//       7         ---     B3
//       GND       ---     GND
int button1_pin = 9;
int button2_pin = 8;
int button3_pin = 7;

#include <thButton.h>
thButton button1(button1_pin); 
thButton button2(button2_pin); 
thButton button3(button3_pin); 


// Các chế độ hoạt động: 
//  1: đo nhiệt độ
//  2: đo độ ẩm
//  3: đo ánh sáng
int mode;  



// Hàm setup() chạy một lần:
void setup() 
{
  Serial.begin(9600);  // khởi tạo kết nối tới máy tính với tốc độ 9600

  sensors.begin();     // cài đặt cảm biến nhiệt độ
  thNumber.begin(thNumber_SDI_pin, thNumber_SCK_pin, thNumber_RCK_pin);  // cài đặt thNumber
  
  // chế độ 1: đo nhiệt độ
  mode = 1;
  Serial.println();
  Serial.print("Mode = ");
  Serial.println(mode);
}



// Hàm loop() chạy lặp lại vô hạn:
void loop() 
{ 
  int sensor_value;  // biến lưu giá trị cảm biến
  
  // kiểm tra nút bấm
  if (button1.onPress())
  {
    mode = 1;
    Serial.println();
    Serial.print("Mode = ");
    Serial.println(mode);
  }	
  else if (button2.onPress())
  {
    mode = 2;
    Serial.println();
    Serial.print("Mode = ");
    Serial.println(mode);
  }
  else if (button3.onPress())
  {
    mode = 3;
    Serial.println();
    Serial.print("Mode = ");
    Serial.println(mode);
  }


  // kiểm tra chế độ hiện tại:
  if (mode == 1)  // chế độ 1: đo nhiệt độ
  {
    sensors.requestTemperatures();              // kích hoạt cảm biến nhiệt độ
    sensor_value = sensors.getTempCByIndex(0);  // đọc giá trị nhiệt độ (C)
  }
  else if (mode == 2)  // chế độ 2: đo độ ẩm
  {
    DHT.read11(dht11_pin);        // kích hoạt cảm biến DHT11
    sensor_value = DHT.humidity;  // giá trị độ ẩm (%)
  }
  else if (mode == 3)  // chế độ 3: đo ánh sáng
  {
    sensor_value = analogRead(light_sensor_pin);  // đọc giá trị cảm biến ánh sáng
  }
  

  // hiển thị giá trị cảm biến:
  thNumber.setNum4(0, sensor_value);  // hiển thị lên thNumber
  Serial.println(sensor_value);       // hiển thị lên màn hình máy tính
  
  delay(250);  // thời gian trễ giữa mỗi lần đọc
}

