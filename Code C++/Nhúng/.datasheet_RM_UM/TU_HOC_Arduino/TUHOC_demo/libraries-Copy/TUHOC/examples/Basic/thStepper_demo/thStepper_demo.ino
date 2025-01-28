// Kết nối Arduino với thStepper:
//    Arduino pin       thStepper pin
//       10        ---    I3
//       11        ---    I2
//       12        ---    I1
//       13        ---    I0
//       VCC      ---     V+
//       GND      ---     GND

int I0_pin = 13;
int I1_pin = 12;
int I2_pin = 11;
int I3_pin = 10;

#include <Stepper.h>
Stepper myStepper(64, I0_pin, I2_pin, I1_pin, I3_pin);

int stepsPerRevolution = 2048;  // số bước để động cơ quay đủ 1 vòng


// Hàm setup() chạy một lần:
void setup() 
{
}


// Hàm loop() chạy lặp lại vô hạn:
void loop() 
{
  int mySpeed = 300;
  myStepper.setSpeed(mySpeed);              // đặt tốc độ = 300
  myStepper.step(stepsPerRevolution);       // quay thuận 1 vòng
  
  delay(1000);                              // dừng 1s

  mySpeed = 150;
  myStepper.setSpeed(mySpeed);              // đặt tốc độ = 150
  myStepper.step(-stepsPerRevolution / 2);  // quay ngược 1/2 vòng
  
  delay(1000);                              // dừng 1s
}