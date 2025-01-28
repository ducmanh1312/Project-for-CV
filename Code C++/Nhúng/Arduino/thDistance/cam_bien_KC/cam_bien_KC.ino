int TRIGGER_PIN = 10;
int ECHO_PIN    = 11;
#include <NewPing.h>
NewPing srf05(TRIGGER_PIN, ECHO_PIN);

int thNumber_SDI_pin = 7;
int thNumber_SCK_pin = 8;
int thNumber_RCK_pin = 9;
#include <thNumber.h>

int button0_pin = 6;
int button1_pin = 5;

#include <thButton.h>
thButton button0(button0_pin); 
thButton button1(button1_pin); 


int flags = 0;
unsigned long time;
void setup() {
  Serial.begin(9600);
  thNumber.begin(thNumber_SDI_pin, thNumber_SCK_pin, thNumber_RCK_pin);
  
}

void clock(int flags)
{
  for (int value = 0; value < 5959; value)
  {
   if((unsigned long)(millis() - time) > 1000 )
   {
    if((value-60)%100 == 0) value+=40;
    if(flags == 0)
    { 
        thNumber.setNum4(0, value);   // hiển thị giá trị value lên thNumber
        thNumber.showDot(2);         // bật hiển thị dấu chấm ở vị trí 0
    }
    time = millis();
    value++;
   }
  }
}

void loop() {
  int distance_cm = srf05.ping_cm();
  Serial.println(distance_cm);  // in kết quả ra màn hình
  
  clock(flags);

//    if (button0.onPress())  // nếu button1 được bấm
//  {
//    Serial.println();
//    Serial.println("button 0 onPress");
//  }

}
