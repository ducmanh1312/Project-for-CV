uint32_t dataPin = 5;// SDI
uint32_t clockPin = 6;//SCK
uint32_t latchPin = 7;//RCK

#define test_seg  0b00000001//g
#define test_seg1 0b00000010//d
#define test_seg2 0b00000100//e
#define test_seg3 0b00001000//a
#define test_seg4 0b00010000//f
#define test_seg5 0b00100000//b
#define test_seg6 0b01000000//dot
#define test_seg7 0b10000000//c

#define num_0 0b10111110
#define num_1 (test_seg5 | test_seg7)
#define num_2 0b00101111
#define num_3 0b10101011
#define num_4 0b10110001
#define num_5 0b10011011
#define num_6 0b10011111
#define num_7 0b10101000
#define num_8 0b10111111
#define num_9 0b10111011
#define dot   0b01000000


uint8_t digital_num[4] = {0B00000000, 0B00000000, 0B00000000, 0B00000000};

//const uint8_t digit_num[10] = {
//  num_0,
//  num_1,
//  num_2,
//  num_3,
//  num_4,
//  num_5,
//  num_6,
//  num_7,
//  num_8,
//  num_9
//};

uint8_t numToDigit(float num)
{
  if(num == 0) return num_0;
  if(num == 1) return num_1;
  if(num == 2) return num_2;
  if(num == 3) return num_3;
  if(num == 4) return num_4;
  if(num == 5) return num_5;
  if(num == 6) return num_6;
  if(num == 7) return num_7;
  if(num == 8) return num_8;
  if(num == 9) return num_9;
}

void shiftByte(uint16_t dataPin,uint16_t clockPin, uint16_t bitOrder,uint8_t val){
   val = ~val;
   for(int i = 0; i < 8; i++)
   {
      if(bitOrder == LSBFIRST)
        digitalWrite(dataPin, !!(val &(1<<i)));
      else
        digitalWrite(dataPin, !!(val & (1<<(8-1-i))));
        
      digitalWrite(clockPin, HIGH);
      digitalWrite(clockPin, LOW);
   }
}

void ledSang4()
{
  for(int i = 0; i < 4; i++)
  {
    shiftByte(dataPin,clockPin,MSBFIRST,digital_num[i]);
  }
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin, LOW);
}


void setDot(int pos)
{
  digital_num[pos] |= dot;
}

void deleDot(int pos)
{
  digital_num[pos] &= ~dot;
}


void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  
  digitalWrite(latchPin, LOW);
  digitalWrite(clockPin, LOW);
}



void loop() {
  
  ledNum40();
  
}


void coutUp()
{
  bitt[3]++;
  if(bitt[3] == 10)
  {
    bitt[3] = 0;
    bitt[2]++;
    if(bitt[2]==10)
    {
      bitt[2] = 0;
      bitt[1]++;
      if(bitt[1]==10) 
      {
        bitt[1] = 0;
        bitt[0]++;
        if(bitt[0] == 10) bitt [0] = 0;
      }
    }
  }
  delay(1000);
}







void shiftOut32(uint32_t dataPin, uint32_t clockPin, uint32_t bitOrder, uint32_t val)
{
   uint32_t i; 
   uint32_t bitt = 32;
   
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
