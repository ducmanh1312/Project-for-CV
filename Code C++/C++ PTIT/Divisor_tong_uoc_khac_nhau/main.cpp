#include <bits/stdc++.h>
using namespace std;

/// @brief 
/// @bug Lỗi ko đóng ngoặc phép toán 

/// @return tổng các số nguyên dương là ước của n nhưng không phải là ước của m.

long long countDivisors(long long n, long long m) 
{
    if(n <= 1) return false; // Lỗi thiếu dòng này
    long long sum = 0;
    for(long long i = 1; i*i <= n ; i++)
    {
        if(n % i == 0) 
        {
            if(m % i != 0) sum += i;
            if( i < n/i) 
            {
                 if(m % (n/i) != 0) sum += n/i; // <-- bug
            }
        }
    }
    return sum;
}


int main()
{
    int i;
    cin >> i;
    while(i--)
    {
        long long n, m;
        cin >> n >> m;
        cout << countDivisors(n, m) << endl;
    }
}