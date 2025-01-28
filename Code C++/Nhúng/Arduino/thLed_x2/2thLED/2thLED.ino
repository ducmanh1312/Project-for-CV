int clockPin = 12;
int latchPin = 10;
int dataPin = 11;
// SDI-DS RCK-latch SCk-clock

const int HC595_COUNT = 2;

byte ledStatus[HC595_COUNT]= {0b01110011,0b00110111}; 

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void shiftOut16(uint16_t dataPin, uint16_t clockPin, uint16_t bitOrder, uint16_t val)
{
   uint16_t bitt = 16;
   digitalWrite(latchPin, LOW);
   for(uint16_t i = 0; i < bitt; i++)
   {
      if(bitOrder == LSBFIRST)
        digitalWrite(d  ataPin, !!(val &(1<<i)));
      else
        digitalWrite(dataPin, !!(val & (1<<(bitt-1-i))));
        
      digitalWrite(clockPin, HIGH);
      digitalWrite(clockPin, LOW);
   }
   digitalWrite(latchPin, HIGH);
}

void shiftOut8(uint16_t dataPin, uint16_t clockPin, uint16_t bitOrder, uint16_t val)
{
    uint16_t bitt = 8;
   digitalWrite(latchPin, LOW);
   for(uint16_t i = 0; i < bitt; i++)
   {
      if(bitOrder == LSBFIRST)
        digitalWrite(dataPin, !!(val &(1<<i)));
      else
        digitalWrite(dataPin, !!(val & (1<<(bitt-1-i))));
        
      digitalWrite(clockPin, HIGH);
      digitalWrite(clockPin, LOW);
   }
   digitalWrite(latchPin, HIGH);
}

void fillValueToArray(byte value) {
  for (int i = 0;i < HC595_COUNT; i += 1) {
    ledStatus[i] = value;
  }
}
void shiftOutHC595(int dataPin, int clockPin, byte ledStatus[]) {
  digitalWrite(latchPin, LOW);
  
  for (int i = 0; i < HC595_COUNT; i++) {
    shiftOut(dataPin,clockPin,MSBFIRST,ledStatus[i]);  // Chúng ta dùng LSBFIRST thay cho MSBFIRST là có lý do của nó, cái này tôi không biết trình như thế nào để bạn hiểu rõ nhất
  }
  digitalWrite(latchPin, HIGH);
}



void loop() {
  uint16_t bitLed = 0b0001111111111110;
    
  shiftOut8(dataPin,clockPin,LSBFIRST, bitLed2);


}
