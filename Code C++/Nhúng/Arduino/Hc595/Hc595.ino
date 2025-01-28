int clockPin = 12;
int latchPin = 10;
int dataPin = 11;
// SDI-DS RCK-latch SCk-clock

int bitLed = 0b00000000;
void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

}
void setLed(int led, bool set)
{
  int note = 0b00000001;
  if (set == HIGH)
  {
    note = (note<<led);
    bitLed = bitLed | note;
  }else
  {
    note = ~(note<<led);
    bitLed = (bitLed&note);
  }
}

void shipOut(int dataPin, int clockPin, int bitOrder, int val)
{
    int i;

    for (i = 0; i < 8; i++)  {
        if (bitOrder == LSBFIRST)
            digitalWrite(dataPin, !!(val & (1 << i)));
        else    
            digitalWrite(dataPin, !!(val & (1 << (7 - i))));

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);        
    }
}


void loop() {
  digitalWrite(latchPin, LOW);
  setLed(1, HIGH);
  setLed(2, HIGH);
  shipOut(dataPin,clockPin,MSBFIRST,bitLed );
  digitalWrite(latchPin, HIGH);
}
