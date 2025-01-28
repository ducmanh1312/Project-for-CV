// Kết nối Arduino với thServo
//    Arduino pin       thServo pin
//        9       ---     CTRL  (orange)
//       VCC      ---     VCC   (red)
//       GND      ---     GND   (brown)

int myServo_pin = 9;

#include <Servo.h>              // sử dụng thư viện Servo
Servo myServo;                  // khai báo myServo


// Hàm setup() chạy một lần
void setup()
{
  int SG90_minPulse =  700;
  int SG90_maxPulse = 2300;
  myServo.attach(myServo_pin, SG90_minPulse, SG90_maxPulse);    // khởi tạo myServo
}


// Hàm loop() chạy lặp lại vô hạn
void loop()
{
  int waittime = 15;            // thời gian đợi servo quay (ms)
  int pos = 90;                 // vị trí servo
  
  for (; pos <= 180; pos += 1)  // quay servo từ 90 đến 180 độ
  { 
    myServo.write(pos);         // quay myServo đến vị trí 'pos'
    delay(waittime);            // đợi servo quay
  }
  for (; pos >= 90; pos -= 1)   // quay servo từ 180 đến 90 độ
  { 
    myServo.write(pos);         // quay myServo đến vị trí 'pos'
    delay(waittime);
  }

  delay(2000);                  // dừng 2 giây
  
  for (; pos >= 0; pos -= 1)    // quay servo từ 90 đến 0 độ
  { 
    myServo.write(pos);
    delay(waittime);
  }
  for (; pos <= 90; pos += 1)   // quay servo từ 0 đến 90 độ
  { 
    myServo.write(pos);
    delay(waittime);
  }

  delay(2000);                  // dừng 2 giây
}

