// Kết nối Arduino với nút bấm:
//    Arduino pin       thButton pin
//       9         ---     B1
//       8         ---     B2
//       GND       ---     GND

int button1_pin = 9;
int button2_pin = 8;

#include <thButton.h>
thButton button1(button1_pin); 
thButton button2(button2_pin); 


// Hàm setup() chạy một lần:
void setup() 
{
  Serial.begin(9600);  // khởi tạo kết nối tới máy tính với tốc độ 9600
}


// Hàm loop() chạy lặp lại vô hạn:
void loop()
{
  if (button1.onPress())  // nếu button1 được bấm
  {
    Serial.println();
    Serial.println("button 1 onPress");
    
    if (button2.isPress())
      Serial.println("button 2 isPress");
    else
      Serial.println("button 2 isRelease");
  }
  
  
  if (button2.onPress())	// nếu button2 được bấm
  {
    Serial.println();
    Serial.println("button 2 onPress");
    
    if (button1.isPress())
      Serial.println("button 1 isPress");
    else
      Serial.println("button 1 isRelease");
  }
  
  delay(50);  // thời gian trễ giữa mỗi lần đọc
}