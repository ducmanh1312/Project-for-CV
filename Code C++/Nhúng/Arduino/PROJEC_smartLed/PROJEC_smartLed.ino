int thLED_SDI_pin = 4;
int thLED_RCK_pin = 5;
int thLED_SCK_pin = 6;
#include <thLed.h>

int trigger_pin = 10;
int echo_pin = 11;
#include <NewPing.h>
NewPing srf05(trigger_pin,echo_pin);

int light_sensor_pin = A3;
int knob_sensor_pin = A5;

void setup() {
  thLed.begin(thLED_SDI_pin,thLED_SCK_pin,thLED_RCK_pin);
  Serial.begin(9600); 
  pinMode(knob_sensor_pin, INPUT);
  pinMode(light_sensor_pin, INPUT);
  pinMode(13, OUTPUT);
}

void led(int status)
{
  for(int i = 0; i < 8; i++)
  {
    if(status == LED_ON) thLed.setLed(i, LED_ON);
    else thLed.setLed(i, LED_OFF);
  }
}

void loop() {
  int light_value = analogRead(light_sensor_pin);
  int distance_cm = srf05.ping_cm();
  int knob_value = analogRead(knob_sensor_pin);

  int threshold = map(knob_value,0,255,0,1023);
    
  if(light_value > threshold || distance_cm < 49 )
  {
      led(LED_ON);
  }else{
      led(LED_OFF);
  }
  
}
