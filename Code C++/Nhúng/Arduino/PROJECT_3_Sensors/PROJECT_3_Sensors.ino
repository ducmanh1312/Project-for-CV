int thNumber_SDI_pin = 7;
int thNumber_SCK_pin = 8;
int thNumber_RCK_pin = 9;
#include <thNumber.h>

int button1_pin = 6;
int button2_pin = 5;
#include <thButton.h>
thButton button1(button1_pin); 
thButton button2(button2_pin); 

int temperature_pin = 2;
#include <OneWire.h>            
#include <DallasTemperature.h>  
  OneWire  oneWire(temperature_pin);
  DallasTemperature  sensors(&oneWire);

int light_sensor_pin = A3;


typedef enum{
  MODE_1 = 1,
  MODE_2 = 2,
  MODE_3 = 3,
} mode_running_t;

  mode_running_t current_mode = MODE_1;
  mode_running_t next_mode;
void setup() {
  Serial.begin(9600); 
  thNumber.begin(thNumber_SDI_pin, thNumber_SCK_pin, thNumber_RCK_pin);
  pinMode(light_sensor_pin, INPUT);  
  sensors.begin();

}

void button()
{
  if(button1.onPress())
  {
    current_mode = next_mode;
    
    Serial.print("current_mode ");    Serial.println(current_mode);
    delay(50);
  }
}

void loop() {
  int light_value = analogRead(light_sensor_pin);
  sensors.requestTemperatures();
//  float temperature = sensors.getTempCByIndex(0);
  
  button();

  switch(current_mode)
  {
    case MODE_1:
      next_mode = MODE_2;
      thNumber.setNum4(0, light_value);
      break;
     case MODE_2:
      next_mode = MODE_1;
      thNumber.setNum4(0, temperature);
      break;
  }
  
}
