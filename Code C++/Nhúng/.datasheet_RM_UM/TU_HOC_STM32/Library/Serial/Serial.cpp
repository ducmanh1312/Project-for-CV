#if defined (STM32F10X_MD)
  #include "stm32f10x_conf.h"
#endif

#if defined (STM32F0XX)
  #include "stm32f0xx_conf.h"
#endif

#include <stdint.h>
#include <stdio.h>
#include "Core.h"
#include "Serial.h"

HardwareSerial Serial;

/**********************************************************************/
void HardwareSerial::begin(uint32_t baud) {
  USART1_begin_A9A10(baud);
}

int HardwareSerial::available() {
  return USART1_available();
}

int HardwareSerial::read() {
  return USART1_read();
}

void HardwareSerial::write(int data) {
  USART1_write(data);
}

int HardwareSerial::peek() {
  return USART1_peek();
}

/**********************************************************************/
void HardwareSerial::printNumber(unsigned long number, int base) {
  switch (base)
  {
    case DEC: printf("%d", number); break;
    case hex: printf("%x", number); break;
    case HEX: printf("%X", number); break;
    case OCT: printf("%o", number); break;
  }
}

#define CONCAT_(A, B)   A ## B
#define CONCAT(A, B)    CONCAT_(A, B)

#define POWER          (uint32_t)(CONCAT(1e, FLOAT_DIGITS))
#define ROUNDING       ((double)0.5 / POWER)

void HardwareSerial::printFloat(double number) {
//  printf("%.*f", FLOAT_DIGITS, number);

  if (number < 0.0)  // negative
  {
    printf("-");
    number = -number;
  }

  number += ROUNDING;
  uint32_t int_part = (uint32_t)(number);
  printf("%u", int_part);

  #if (FLOAT_DIGITS > 0)
		double remain = number - (uint32_t)number;
		uint32_t digit_part = (uint32_t)(remain * POWER);
		printf(".%0*d", FLOAT_DIGITS, digit_part);
  #endif
}

/**********************************************************************/
void HardwareSerial::print(const char c[]) {
  printf("%s", c);
}

void HardwareSerial::print(char c) {
  printf("%c", c);
}

void HardwareSerial::print(unsigned char number, int base) {
  printNumber(number, base);
}

void HardwareSerial::print(int number, int base) {
  printNumber(number, base);
}

void HardwareSerial::print(unsigned int number, int base) {
  printNumber(number, base);
}

void HardwareSerial::print(long number, int base) {
  printNumber(number, base);
}

void HardwareSerial::print(unsigned long number, int base) {
  printNumber(number, base);
}

void HardwareSerial::print(double number) {
  printFloat(number);
}

/**********************************************************************/
void HardwareSerial::println() {
  printf("\n");
}

void HardwareSerial::println(const char c[]) {
  printf("%s", c);
  println();
}

void HardwareSerial::println(char c) {
  printf("%c", c);
  println();
}

void HardwareSerial::println(unsigned char number, int base) {
  printNumber(number, base);
  println();
}

void HardwareSerial::println(int number, int base) {
  printNumber(number, base);
  println();
}

void HardwareSerial::println(unsigned int number, int base) {
  printNumber(number, base);
  println();
}

void HardwareSerial::println(long number, int base) {
  printNumber(number, base);
  println();
}

void HardwareSerial::println(double number) {
  printFloat(number);
  println();
}

/**********************************************************************/
