#include <bits/stdc++.h>
using namespace std;


// Hàm tính tổng ước số của n
bool isPerfectNumber(long long n) 
{
    if(n <= 1) return false;
    long long result = 1;
    for(long long i = 2; i*i <= n ; i++)
    {
        if(n % i == 0) 
        {
            result += i;
            if( i != n/i) result += n/i;
        }
    }
    return result == n ;
}

// hàm tính tổng ước số nhỏ hơn n
long long countDivisors(long long n) 
{
    if(n <= 1) return false; // Lỗi thiếu dòng này
    long long result = 0;
    for(long long i = 1; i*i <= n ; i++)
    {
        if(n % i == 0) 
        {
            result += i;
            if( i != n/i && n/i < n) result += n/i;
        }
    }
    return result;
}


int main()
{
    int i;
    cin >> i;
    while(i--)
    {
        long long a;
        cin >> a;
        cout << countDivisors(a) << endl;
    }
}