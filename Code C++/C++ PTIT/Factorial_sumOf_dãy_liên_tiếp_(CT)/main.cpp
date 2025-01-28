#include <bits/stdc++.h>
using namespace std;

/// @brief  công thức N = a+(a+1)+...+(a+L) = (L+1)*a + L*(L+1)/2
/// @bug
/// @return số cách biểu diễn của N! thành tổng của hai số tự nhiên liên tiếp trở lên.



void count(long long num, long long m)
{
    int res = 0;
    long long n = 1;

    for (long long L = 1; L * (L + 1) < 2 * n; L++)
    {
        double a = (n*1.0 - ((L * (L + 1) / 2))) / (L+1); // ép kiểu n
        if(a - (long long)a == 0.0)
        {
            res++;
        }
    }
    cout << (res % m) << endl;
}




int main()
{

    int test;
    cin >> test;

    while (test--)
    {
        long long n, m;
        cin >> n >> m;

        count(n, m);
    }
}