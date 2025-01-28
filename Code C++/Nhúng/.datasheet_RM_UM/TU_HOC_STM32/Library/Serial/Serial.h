#ifndef __SERIAL_H__
#define __SERIAL_H__

/**********************************************************************/
#define FLOAT_DIGITS   2

#define DEC 10
#define hex 16
#define HEX 17
#define OCT 8

/**********************************************************************/
class HardwareSerial
{
  public:
  void begin(unsigned long baud);
//  void end();

  int available();
  int peek();
  int read();
  void flush();
  void write(int data);

  void printNumber(unsigned long, int);
  void printFloat(double);

  void print(const char []);
  void print(char);
  void print(unsigned char, int = DEC);
  void print(int, int = DEC);
  void print(unsigned int, int = DEC);
  void print(long, int = DEC);
  void print(unsigned long, int = DEC);
  void print(double);

  void println(const char []);
  void println(char);
  void println(unsigned char, int = DEC);
  void println(int, int = DEC);
  void println(unsigned int, int = DEC);
  void println(long, int = DEC);
  void println(unsigned long, int = DEC);
  void println(double);

  void println();
};

extern HardwareSerial Serial;

/**********************************************************************/
#endif // __SERIAL_H__

