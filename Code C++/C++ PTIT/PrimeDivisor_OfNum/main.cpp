#include <bits/stdc++.h>

using namespace std;

bool isPrime(long long n)
{
    if(n == 1) return true;

    for(int i = 2; i*i <= n; i++)
    {
        if(n % i == 0) return true;
    }
    return false;
}

/// @brief 
/// @param n 
/// @return: số lượng ước nguyên tố của n
bool countPrimeDivisors(long long n)
{
    long long pas = n;
    long long count = 0;
    for(int i = 2; i <= n; i++)
    {
        if(n % i == 0) 
        {
            if(isPrime(i)) count++;
            while(n % i == 0 ) n /= i;
        }
    }
    return count < pas;
}

int main()
{
    int test;
    cin >> test;
    while(test--)
    {
        long long n;
        cin >> n;
        cout << countPrimeDivisors(n) << endl;
    }
}
