int but = 8;
int led = 13;
int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;  // Thời gian trước đó
unsigned long debounceDelay = 50;    // Thời gian chờ giữa các lần đọc
unsigned long pressThreshold = 100;  // Ngưỡng thời gian nhấn tối thiểu

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);  
  pinMode(but, INPUT_PULLUP);
  digitalWrite(led, LOW);

}

void loop()
{
  digitalWrite(led, LOW);
  int reading = digitalRead(but);
  //Serial.println(millis()); delay(100);
  if(reading != lastButtonState )
  {
    lastDebounceTime = millis();
  } 
    

    if(millis()-lastDebounceTime > debounceDelay )
    {
      if(reading != buttonState )
      {
        buttonState = reading;

       if(buttonState == LOW)
        {

          Serial.println("Nút nhấn đã được nhấn");
          digitalWrite(led,HIGH);
          delay(200);
        }else
        {
          Serial.println("Nút nhấn đã được nhả ra");
          digitalWrite(led,LOW);
          delay(200);        
        }
      }
    }
  lastButtonState = reading;
}
