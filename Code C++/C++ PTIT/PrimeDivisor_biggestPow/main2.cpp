#include <iostream>
#include <cmath>
using namespace std;

/// @brief lặp 2 đến sqrt(n) với bước nhảy j += 2
/// @return tìm ước số dạng a^b của n sao cho b lớn nhất
///

void biggestPow(long long n)
{
    long long a[1000], b[1000]; //  Khai báo hai mảng a và b để lưu ước số và số lần xuất hiện tương ứng.
    long long min = -1, max = 0, i = 0;

    for (long long j = 2; j <= sqrt(n); (j < 3) ? j++ : j += 2)
    {
        int mark = 0;
        if (n % j == 0)
        {
            a[i] = j;
            b[i] = 0;
            mark++;
        }
        while (n % j == 0)
        {
            b[i]++;
            n /= j;
        }
        if (mark != 0)
        {

            if (b[i] > max)
            {
                max = b[i];
                min = a[i];
            }
            i++;
        }
    }

    if (n > 1)
    {
        if (max < 1)
        {
            max = 1;
            min = n;
        }
    }
    cout << min << " " << max << endl;
}


int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long n;
        cin >> n;
        biggestPow(n);
    }
}