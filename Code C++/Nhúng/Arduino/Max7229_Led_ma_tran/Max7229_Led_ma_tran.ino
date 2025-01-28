#define DIN_PIN 7   // Pin dữ liệu (data in) kết nối với MAX7219
#define CS_PIN 6    // Pin chọn (chip select) kết nối với MAX7219
#define CLK_PIN 5   // Pin xung (clock) kết nối với MAX7219

// Khai báo các thanh ghi (registers) của MAX7219
#define MAX7219_NOOP 0x00
#define MAX7219_DIGIT0 0x01
#define MAX7219_DIGIT1 0x02
#define MAX7219_DIGIT2 0x03
#define MAX7219_DIGIT3 0x04
#define MAX7219_DIGIT4 0x05
#define MAX7219_DIGIT5 0x06
#define MAX7219_DIGIT6 0x07
#define MAX7219_DIGIT7 0x08
#define MAX7219_DECODEMODE 0x09
#define MAX7219_INTENSITY 0x0A
#define MAX7219_SCANLIMIT 0x0B
#define MAX7219_SHUTDOWN 0x0C
#define MAX7219_DISPLAYTEST 0x0F

byte matrix[8] = {
  0B00000000,
  0B00000000,
  0B00000000,
  0B00000000,
  0B00000000,
  0B00000000,
  0B00000000,
  0B00000000,
};

void sendMax7219(byte reg, byte data)
{
  digitalWrite(CS_PIN, LOW);
  shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, reg);
  shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, data);
  digitalWrite(CS_PIN, HIGH);
}

void initMax7219()
{
  sendMax7219(MAX7219_SCANLIMIT, 7);
  sendMax7219(MAX7219_DECODEMODE, 0);
  sendMax7219(MAX7219_DISPLAYTEST, 0);
  sendMax7219(MAX7219_INTENSITY, 15);
  sendMax7219(MAX7219_SHUTDOWN, 1);
}

void displayMatrix()
{
  for(int row = 0; row < 8; row++)
  {
    sendMax7219(row+1, matrix[row]);
  }
}

void setMatrixValue(int x, int y, bool value) 
{
  if(x >= 0 && x <8 && y >= 0 && y < 8)
  {
    if(value)
    {
      matrix[y] |= (1<<x);
    }else
    {
      matrix[y] &= ~(1<<x);
    }
  }
}

void setup() {
  pinMode(DIN_PIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  Serial.begin(9600);
  initMax7219();
}

void loop() {
    for(int i = 0; i < 8; i++)
    {
      setMatrixValue(i, i, true);    // Bật LED tại vị trí (i, i)
      displayMatrix();               // Hiển thị ma trận
      delay(50);                    // Delay 200ms
      setMatrixValue(i, i, false);   // Tắt LED tại vị trí (i, i)
    }

  

}
