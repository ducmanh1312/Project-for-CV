int clockPin = 12; //SH_CP  // SCK
int latchPin = 10; //ST_CP  // RCK
int dataPin = 11;  //DS     // SDI
int DIG2_PIN = 9;
int DIG1_PIN = 8;

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

uint8_t digital_num[4] = {0B00000000, 0B00000000};

uint8_t numToDigit(float num)
{
  if (num == 0) return num_0;
  if (num == 1) return num_1;
  if (num == 2) return num_2;
  if (num == 3) return num_3;
  if (num == 4) return num_4;
  if (num == 5) return num_5;
  if (num == 6) return num_6;
  if (num == 7) return num_7;
  if (num == 8) return num_8;
  if (num == 9) return num_9;
}


void shiftOut8(uint16_t dataPin, uint16_t clockPin, uint16_t bitOrder, uint16_t val)
{
  uint16_t bitt = 8;
  digitalWrite(latchPin, LOW);
  delay(5);
  for (uint16_t i = 0; i < bitt; i++)
  {
    if (bitOrder == LSBFIRST)
      digitalWrite(dataPin, !!(val & (1 << i)));
    else
      digitalWrite(dataPin, !!(val & (1 << (bitt - 1 - i))));

    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
  }
  digitalWrite(latchPin, HIGH);
  delay(5);
}

void plexLed(int num, int digit)
{
  shiftOut8(dataPin, clockPin, LSBFIRST, digit);
  if (num == 1)
  {
    digitalWrite(DIG1_PIN, LOW);
    digitalWrite(DIG2_PIN, HIGH);
  } else
  {
    digitalWrite(DIG2_PIN, LOW);
    digitalWrite(DIG1_PIN, HIGH);
  }
}

int setLed(int num)
{
  int n = num % 10;
  (digital_num[1] &= !dot) |= numToDigit(n);
  num /= 10;
  (digital_num[0] &= !dot) |= numToDigit(num);

  plexLed(1, digital_num[0]);
  plexLed(2, digital_num[1]);
}


void setup() {
  Serial.begin(9600);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(DIG2_PIN, OUTPUT);
  pinMode(DIG1_PIN, OUTPUT);

  digitalWrite(DIG2_PIN, LOW);
  digitalWrite(DIG1_PIN, LOW);

}

int i = 0;
uint32_t time = 0;
void loop() {

  if (millis() - time > 50)
  {
    time = millis();
    i++;
    if (i >= 100) i = 0;
  }
  setLed(i);



}
