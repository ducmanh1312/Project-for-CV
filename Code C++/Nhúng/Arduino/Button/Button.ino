uint32_t dataPin = 10;// SDI
uint32_t clockPin = 11;//SCK
uint32_t latchPin = 12;//RCK

const int buttonPin = 8;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin



int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(13, OUTPUT);
  
  digitalWrite(latchPin, LOW);
  digitalWrite(clockPin, LOW);
}

void shiftOut16(uint16_t dataPin, uint16_t clockPin, uint16_t bitOrder, uint16_t val)
{
   uint16_t i; 
   uint16_t bitt = 16;
   
   for(i = 0; i < bitt; i++)
   {
      if(bitOrder == LSBFIRST)
        digitalWrite(dataPin, !!(val &(1<<i)));
      else
        digitalWrite(dataPin, !!(val & (1<<(bitt-1-i))));
        
      digitalWrite(clockPin, HIGH);
      digitalWrite(clockPin, LOW);
   }

   digitalWrite(latchPin, HIGH);
   digitalWrite(latchPin, LOW);

}

void loop() {

  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);

  if (buttonState == HIGH) {
    shiftOut16(dataPin, clockPin, LSBFIRST, 0b1111111111111111);
    delay(2000);
  } else {
    shiftOut16(dataPin, clockPin, LSBFIRST, ~0b1111111111111111);
    delay(200);
  }
  delay(100);
}
