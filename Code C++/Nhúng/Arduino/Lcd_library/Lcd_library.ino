#include "tyu.h"
#include <Wire.h>
#include "Print.h" 
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
int led = 13;

#define printIIC(args)  Wire.write(args) // Hàm 

  uint8_t _Addr;
  uint8_t _displayfunction;
  uint8_t _displaycontrol;
  uint8_t _displaymode;
  uint8_t _numlines;
  uint8_t _cols;
  uint8_t _rows;
  uint8_t _backlightval;

// 
void LiquidCrystal_I22C(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows)
{
  _Addr = lcd_Addr;
  _cols = lcd_cols;
  _rows = lcd_rows;
  _backlightval = LCD_NOBACKLIGHT;
}


/************ low level data pushing commands **********/
void expanderWrite(uint8_t _data) // Hàm gửi dữ liệu tới thanh ghi
{
  Wire.beginTransmission(_Addr);
  printIIC((int)(_data) | _backlightval);
  Wire.endTransmission();
}

void pulseEnable(uint8_t _data) // Gửi dữ liệu điều khiển chân Enable
{
  expanderWrite(_data | En);
  delayMicroseconds(1);
  expanderWrite(_data & ~En);
  delayMicroseconds(50);
}

void write4bits(uint8_t value) // Hàm gửi 4 bit dữ liệu đến thanh ghi
{
  expanderWrite(value);
  pulseEnable(value);
}

void send(uint8_t value, uint8_t mode) // Hàm gửi 8 bit dữ liệu đến thanh ghi
{
  uint8_t highnib = value & 0xf0;
  uint8_t lownib = (value<<4)& 0xf0;
  write4bits((highnib)|mode);
  write4bits((lownib)|mode); 
}

inline void write(uint8_t value) { // Gửi 8 bit dữ liệu đến chân Rs => in ra màn
  send(value, Rs);
  return 1;
}

/*********** mid level commands, for sending data/cmds */
inline void command(uint8_t value) // mode 0 => gửi 8 bit lệnh đến lcd
{
  send(value, 0);
}

// Turn the display on/off (quickly)
void display()
{
  _displaycontrol |= LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void noDisplay()
{
  _displaycontrol &= ~LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void cursor() 
{
  _displaycontrol |= LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void noCursor() 
{
  _displaycontrol &= ~LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

/********** high level commands, for the user! */
void clear()
{
  command(LCD_CLEARDISPLAY);
  delayMicroseconds(2000);
}

void home()
{
  command(LCD_RETURNHOME);
  delayMicroseconds(2000);
}

void setCursor(uint8_t row, uint8_t col)
{
  int offset[] = {0x00, 0x40, 0x14, 0x54};
  if ( row >= _numlines)
  {
    row = _numlines -1;
  }
  command(LCD_SETDDRAMADDR | (col + offset[row]));
}

// Turn the (optional) backlight off/on
void backlight()
{
  _backlightval = LCD_BACKLIGHT;
  expanderWrite(0);
}

void noBacklight() 
{
  _backlightval=LCD_NOBACKLIGHT;
  expanderWrite(0);
}


void begin(uint8_t cols, uint8_t lines)
{
  if (lines > 1) {
    _displayfunction |= LCD_2LINE;
  }

  _numlines = lines;
  delay(50);

  expanderWrite(_backlightval);
  delay(1000);

  write4bits(0x03 << 4);
  delayMicroseconds(4500); // wait min 4.1ms
   
  // second try
  write4bits(0x03 << 4);
  delayMicroseconds(4500); // wait min 4.1ms
   
  // third go!
  write4bits(0x03 << 4); 
  delayMicroseconds(150);
   
  // finally, set to 4-bit interface
  write4bits(0x02 << 4);

  command(LCD_FUNCTIONSET | _displayfunction);

  _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
  
  display();

  clear();

  _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  command(LCD_ENTRYMODESET | _displaymode);

  home();

}

void initt()
{
  Wire.begin();
  _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
  begin(_cols, _rows);  
}
//------------------------------------------------------------------//

void lcdWriteChar(char c)
{
  Wire.beginTransmission(_Addr);
  write(c);                        // Gửi 8 bit dữ liệu đến chân Rs => in ra màn
  Wire.endTransmission();
}

void print(const char* str)
{
  while(*str)
  {
    lcdWriteChar(*str);
    str++;
  }
}



void setup()
{
  Serial.begin(9600);
  LiquidCrystal_I22C(0x27,16,2);
  initt();                   
  backlight();
  setCursor(0,0);
  print("I");

    
}


void loop() 
{
    if(Serial.available())
  {
    String text = Serial.readStringUntil('(');
    char command[20];
    text.toCharArray(command, sizeof(command));

    if(text == "CLEAR") {
        clear();
    }else if(text == "PRINT")
    {
      text = Serial.readStringUntil(',');
      char row[20];
      text.toCharArray(row, sizeof(row));
      int ROW = atoi(row);
      
      text = Serial.readStringUntil(',');
      char col[20];
      text.toCharArray(col, sizeof(col));
      int COL = atoi(col);
      
      setCursor(ROW,COL);

      text = Serial.readStringUntil(')');
      text.toCharArray(command, sizeof(command));
      print(command);
    }else
    {
      print(command);
    }
    text = Serial.readStringUntil('\n');
  }
  
}
