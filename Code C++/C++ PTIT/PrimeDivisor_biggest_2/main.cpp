#include <bits/stdc++.h>
using namespace std;

/// @brief lặp qua các ước lẻ 
/// @param n
/// @return trả về số có ước số nguyên tố lớn nhất trong khoảng từ L đến R, nếu có nhiều hơn 1số thì hiển thị số có giá trị lớn nhất.

// Hàm trả về ước nguyên tố lớn nhất của n
long long gpf(long long n)
{
    long long maxprime = 0;
    while (n % 2 == 0)
    {
        maxprime = 2;
        n >>= 1;
    }
    while (n % 3 == 0)
    {
        maxprime = 3;
        n /= 3;
    }
    for (long i = 6; i-1 <= sqrt(n); i += 6)
    {
        while (n % (i-1) == 0)
        {
            maxprime = i-1;
            n /= i-1;
        }
        
        long i2 = i + 1;
        while (n % i2 == 0)
        {
            maxprime = i2;
            n /= i2;
        }
    }
    if (n > 4)
    {
        maxprime = n;
    }
    return maxprime;
}


int main()
{
    long long t, l, r, max = 0;
    cin >> t;
    while (t--)
    {
        cin >> l >> r;
        max = 0;
        while(l <= r) // Lặp qua các số từ l đến r
        {
        	long long temp = gpf(l);
        	if(max < temp) max = temp;
        	if(l % 2 == 1) l += 2;
        	else l++;
        	
		}
		cout << max << endl;
    }
    return 0;
}
