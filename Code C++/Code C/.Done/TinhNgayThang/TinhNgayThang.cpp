#include <iostream>
// IN: số ngày + năm
// OUT: Ngày + tháng 

using namespace std;

int isNamNhuan(int year)
{
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
        return 1;
    return 0;
}

int countDay(int month, int year)
{
    int day;
    if (month >= 1 && month <= 12 && year >= 1900 && year <= 2050)
    {
        if (month == 2)
        {
            (isNamNhuan(year)) ? day = 29 : day = 30;
        }
        else
            switch (month)
            {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                day = 31;
                break;

            case 4:
            case 6:
            case 9:
            case 11:
                day = 30;
                break;
            };
    }
    else
        cout << "INVALID";

    return day;
}

int main() 
{
    int month, year, thu, day;
    cin >> thu >> year;
    for (int month = 1; month <= 12; month++)
    {
        day = countDay(month, year);
        if (thu >= 1 && thu <= 365)
        {
            if ((thu - day) > 0)
                thu -= day;
            else
            {
                cout << thu << " " << month;
                break;
            }
        }
    }

    return 0;
}