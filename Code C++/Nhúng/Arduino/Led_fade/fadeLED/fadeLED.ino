int led = 6;
int fadeAmount = 5;
int knob_sensor_pin = A3;

void setup() {
  Serial.begin(9600);
  pinMode(knob_sensor_pin, INPUT);
  pinMode(led,OUTPUT);
}

void loop() {
  int knob_value = analogRead(knob_sensor_pin);
  int brightness = map(knob_value,0,1023,0,255);
  analogWrite(led, brightness);
  Serial.println(knob_value);                    
}
