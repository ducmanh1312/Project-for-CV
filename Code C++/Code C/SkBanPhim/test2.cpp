#include <iostream>
#include <cmath>
#include <fstream>
#include <conio.h>

#define FOR(i, start, end) for (int i = start; i <= end; i++)
#define FOD(i, end, start) for (int i = end; i <= start; i--)
#define ll long long
#define ull unsigned long long
using namespace std;

// NGUYÊN MẪU HÀM
int UCLN(int, int);
// NẠP CHỒNG HÀM: đặt tên 2 hàm giống nhau nhưng khác tham số truyền vào

// NGUYÊN MẪU HÀM

//
template <class p1>

int main()
{
    char key_press;
    int ascii_value;
    cout << "\n\t\tNhap phim bat ky de kiem tra ma ASCII\n\t\tn ESC de thoat\n\n\n";
    while (1)
    {
        key_press = getch();
        ascii_value = key_press;
        if (ascii_value == -32)
        {
            key_press = getch();
            ascii_value = key_press;
        }
        if (ascii_value == 27)
            break;
        cout << "Ban nhap phim-> \" " << key_press << " \" Gia tri ASCII =  " << ascii_value << "\n";
    }
    return 0;
}

/*
    
*/