#include <bits/stdc++.h>
using namespace std;


/// @brief 
/// @param n 
/// @return Trả về tổng ước số lớn nhất của các số nhỏ hơn n

long long sumsnt(long long n)
{
    long long sum = 0;
    long long a[n + 1]; // Mảng chứa số mũ lớn nhất của a[i]
    memset(a,0,sizeof(a));


    for(long long i = 2; i <= n/2; i++)
    {
        if(a[i] == 0)
        {
            for(long long j = i*2; j <= n; j += i)
            {
                a[j] = i;
            }
        }
    }

    for(long long i = 2; i <= n; i++)
    {
        if(a[i])
        {
            sum += a[i];
        }else
        {
            sum += i;
        }
    }
    return sum;
}

int main()
{
    int test;
    cin >> test;
    while(test--)
    {
        long n;
        cin >> n;
        cout << sumsnt(n) << endl;
    }
}





