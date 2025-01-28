// Kết nối Arduino với cảm biến ánh sáng:
//    Arduino pin       thLight pin
//       A3        ---     OUT
//       VCC       ---     V+
//       GND       ---     GND
int light_sensor_pin = A3;


// Kết nối Arduino với thRTC:
//    Arduino pin        thRTC pin
//       A4        ---     SDA
//       A5        ---     SCL
//       VCC       ---     VCC
//       GND       ---     GND
#include <Wire.h>
#include <TimeLib.h>    // https://github.com/PaulStoffregen/Time/archive/master.zip
#include <DS1307RTC.h>  // https://github.com/PaulStoffregen/DS1307RTC/archive/master.zip


// Kết nối Arduino với nút bấm:
//    Arduino pin       thButton pin
//       9         ---     B2
//       A0        ---     B4
//       GND       ---     GND
int buttonUp_pin = 9;
int buttonDown_pin = A0;

#include <thButton.h>
thButton buttonUp(buttonUp_pin); 
thButton buttonDown(buttonDown_pin); 


// Kết nối Arduino với thStepper:
//    Arduino pin       thStepper pin
//       10        ---    I3
//       11        ---    I2
//       12        ---    I1
//       13        ---    I0
//       VCC      ---     V3
//       GND      ---     GND
int I0_pin = 13;
int I1_pin = 12;
int I2_pin = 11;
int I3_pin = 10;

#include <Stepper.h>
Stepper myStepper(64, I0_pin, I2_pin, I1_pin, I3_pin);
int myStep = 2048;  // số bước động cơ sẽ quay


// trạng thái hiện tại của rèm: true = kéo lên, false = kéo xuống
bool blind_status = true;  




// Hàm setup() chạy một lần:
void setup() 
{
  Serial.begin(9600);                // khởi tạo kết nối tới máy tính với tốc độ 9600
  pinMode(light_sensor_pin, INPUT);  // cấu hình INPUT để đọc giá trị cảm biến
  myStepper.setSpeed(300);           // đặt tốc độ động cơ = 300
}



// Hàm loop() chạy lặp lại vô hạn:
void loop() 
{ 
  // Kiểm tra nút bấm:
  if (buttonUp.onPress())         // nếu bấm nút UP thì kéo rèm lên
  {
    blind_up();
  }
  else if (buttonDown.onPress())  // nếu bấm nút DOWN thì kéo rèm xuống
  {
    blind_down();
  }
  
  
  // kiểm tra điều kiện ánh sáng: nếu trời tối thì kéo rèm lên
  int light_value = analogRead(light_sensor_pin);  // đọc giá trị cảm biến ánh sáng
  if (light_value > 600)                           // so sánh với giá trị ngưỡng
  {
    blind_up();
  }
  

  // kiểm tra thời gian trong ngày:
  tmElements_t  currentTime;
  RTC.read(currentTime);  // đọc thời gian từ RTC
  if (currentTime.Hour == 7 && currentTime.Minute == 30)        // kéo rèm lên lúc 7h30 sáng
  {
    blind_up();
  }
  else if (currentTime.Hour == 12 && currentTime.Minute == 15)  // kéo rèm xuống lúc 12h15 trưa
  {
    blind_down();
  }
  
} // end loop



// Hàm thực hiện kéo rèm lên:
void blind_up()
{
  if (blind_status != true)   // nếu rèm chưa được kéo lên
  {
    Serial.println();
    Serial.println("Dang keo rem len...");
    myStepper.step(-myStep);  // kéo rèm lên
    blind_status = true;      // cập nhật trạng thái của rèm
    Serial.println("Rem da duoc keo len!");
  }
}


// Hàm thực hiện kéo rèm xuống:
void blind_down()
{
  if (blind_status != false)  // nếu rèm chưa được kéo xuống
  {
    Serial.println();
    Serial.println("Dang keo rem xuong...");
    myStepper.step(myStep);   // kéo rèm xuống
    blind_status = false;     // cập nhật trạng thái của rèm
    Serial.println("Rem da duoc keo xuong!");
  }
}
