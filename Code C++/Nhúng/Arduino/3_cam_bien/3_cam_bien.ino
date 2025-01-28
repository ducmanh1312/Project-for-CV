int TRIGGER_PIN = 10;
int ECHO_PIN    = 11;
#include <NewPing.h>
NewPing srf05(TRIGGER_PIN, ECHO_PIN);

int thNumber_SDI_pin = 7;
int thNumber_SCK_pin = 8;
int thNumber_RCK_pin = 9;
#include <thNumber.h>

int button0_pin = 6;
int button2_pin = 5;
int button4_pin = 4;
#include <thButton.h>
thButton button0(button0_pin); 
thButton button2(button2_pin); 
thButton button4(button4_pin); 

int temperature_pin = 2;
#include <OneWire.h>            
#include <DallasTemperature.h> 
OneWire  oneWire(temperature_pin);
DallasTemperature  sensors(&oneWire);

typedef enum
{
  MODE_1 = 1,
  MODE_2 = 2,
  MODE_3 = 3,  
} mode_running_t;

  int flags = 0, value = 0, speed;
  mode_running_t current_mode, next_mode;
  unsigned long time, timeClock, second, minute;
void setup() {
  Serial.begin(9600);
  thNumber.begin(thNumber_SDI_pin, thNumber_SCK_pin, thNumber_RCK_pin);
  sensors.begin();
  current_mode = MODE_1;
}

void clock()
{
   speed = 200;
   if((unsigned long)(millis() - timeClock) > speed)
   {
      if(second < 59)
      {
        timeClock = millis();
        second++;
      }else
      {
        second = 0;
        if(minute < 59) minute++;
        else minute = 0;
      }
   }
}

void displayClock()
{
  if(second >= 60)second = 0;
  if(minute >= 60) { minute = 0; second = 0;}
  thNumber.setNum2(0, second);
  thNumber.setNum2(2, minute);
  thNumber.showDot(2);         // bật hiển thị dấu chấm ở vị trí 0
}

void display(int val)
{
  thNumber.setNum4(0, val);
}

void displayFloat(float val)
{
  int i = 3;
  float k = 10, m = 1000;
  while(val >= k)
  {
    k*= 10;
    m /= 10;
    i--;
  }
  display(val*m);
  thNumber.showDot(i);
}

void button()
{
  if (button0.onPress())
  {
    current_mode = next_mode;
    
    Serial.print("mode = ");  Serial.println(current_mode); delay(200);
  }
  if(current_mode == MODE_1)
  {
    if (button2.onPress())
    {
      minute+= 1;
      displayClock();
    }
    if(button4.onPress())
    {
      minute--;
      displayClock();
    }
  }
}

void distance()
{
  if((unsigned long)(millis() - time) > 300)
  {
    time = millis();
    int distance_cm = srf05.ping_cm();
    display(distance_cm);
  }
}

void temperature()
{
  if((unsigned long)(millis() - time) > 300)
  {
    time = millis();
    sensors.requestTemperatures();
    float temperature_C = sensors.getTempCByIndex(0);  
    displayFloat(temperature_C);
    
    Serial.println(temperature_C);
  }
}

void loop() {
  clock();
  button();
  
  switch(current_mode)
  {
    case MODE_1:
      next_mode = MODE_2;
      displayClock();
      break;
     case MODE_2:
      next_mode = MODE_3;
      distance();
      break;
     case MODE_3:
      next_mode = MODE_1;
      temperature();
      break;
  }

}
