int led = 2;
int knob_sensor_pin = A3;

void setup() {
  Serial.begin(9600);
  pinMode(knob_sensor_pin, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  int knob_value = analogRead(knob_sensor_pin);
  if(knob_value < 400){
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led, LOW);
  }
}
