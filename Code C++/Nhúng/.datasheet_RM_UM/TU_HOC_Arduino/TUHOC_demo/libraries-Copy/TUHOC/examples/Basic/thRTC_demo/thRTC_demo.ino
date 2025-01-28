// Kết nối Arduino với thRTC:
//    Arduino pin        thRTC pin
//       A4        ---     SDA
//       A5        ---     SCL
//       VCC       ---     VCC
//       GND       ---     GND

#include <Wire.h>
#include <TimeLib.h>    // https://github.com/PaulStoffregen/Time/archive/master.zip
#include <DS1307RTC.h>  // https://github.com/PaulStoffregen/DS1307RTC/archive/master.zip


// Hàm setup() chạy một lần:
void setup() 
{
  Serial.begin(9600);  // khởi tạo kết nối tới máy tính với tốc độ 9600
}


// Hàm loop() chạy lặp lại vô hạn:
void loop() 
{
  tmElements_t  currentTime;
  RTC.read(currentTime);  // đọc dữ liệu từ RTC

  // hiển thị: ngày / tháng / năm
  Serial.print(currentTime.Day);
  Serial.print("/");
  Serial.print(currentTime.Month);
  Serial.print("/");
  Serial.print(tmYearToCalendar(currentTime.Year));
  
  // hiển thị: giờ : phút : giây
  Serial.print(", ");
  print2digits(currentTime.Hour);
  Serial.print(":");
  print2digits(currentTime.Minute);
  Serial.print(":");
  print2digits(currentTime.Second);
  Serial.println();

  delay(1000);  // cách 1s đọc một lần
}


void print2digits(int number)
{
  if (number >= 0 && number < 10)
    Serial.write('0');
    
  Serial.print(number);
}