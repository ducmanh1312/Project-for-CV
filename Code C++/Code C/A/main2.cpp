#include <stdio.h>
#include <math.h>

void separateDigits(float number) {
    int integerPart = (int)number; // Phần nguyên của số thực
    float fractionalPart = number - integerPart; // Phần thập phân của số thực

    printf("Integer part: %d\n", integerPart);
    printf("Fractional part: %.3f\n", fractionalPart);

    // Tách các chữ số từ phần nguyên
    int digit;
    int divisor = 1;
    while (integerPart / divisor > 0) {
        divisor *= 10; // Tăng số chữ số
    }
    divisor /= 10; // Chuyển lại số chữ số cuối cùng

    while (divisor > 0) {
        digit = integerPart / divisor; // Lấy chữ số
        printf("Digit: %d\n", digit);
        integerPart %= divisor; // Loại bỏ chữ số đã lấy
        divisor /= 10; // Giảm số chữ số
    }

    // Tách các chữ số từ phần thập phân
    int decimalPlaces = 3; // Số chữ số thập phân cần tách
    int decimalDigit;
    for (int i = 0; i < decimalPlaces; i++) {
        fractionalPart *= 10; // Dịch phần thập phân sang trái
        decimalDigit = (int)fractionalPart; // Lấy chữ số thập phân
        printf("Decimal digit: %d\n", decimalDigit);
        fractionalPart -= decimalDigit; // Loại bỏ chữ số thập phân
    }
}

int main() {
    float number = 10.23; // Số thực đầu vào

    separateDigits(number);

    return 0;
}

 // float number = 10.23; // Số thực đầu vào

  // int intergerNUm = 0, temp = 1;

  // int intergerNum = (int)number;
 

  // float fractionalPart = number - intergerNum; // Phần thập phân của số thực
  // int decimalPlaces = 3;                       // Số chữ số thập phân cần tách
  // int decimalDigit;
  // for (int i = 0; i < decimalPlaces; i++)
  // {
  //   fractionalPart *= 10;               // Dịch phần thập phân sang trái
  //   decimalDigit = (int)fractionalPart; // Lấy chữ số thập phân
  //   printf("Decimal digit: %d\n", decimalDigit);
  //   fractionalPart -= decimalDigit; // Loại bỏ chữ số thập phân
  // }

  // return 0;