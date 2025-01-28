#include <bits/stdc++.h>
using namespace std;

// dem so chinh phuong trong khoang a, b
int countPerfectSquare(long long a, long long b)
{
    int k = 0;
    long long sqrta = sqrt(a);
    long long sqrtb = sqrt(b);

    if(sqrta * sqrta < a) sqrta++;
    k = sqrtb - sqrta +1;
    return k;
}

bool isPerfectSquare(long long n)
{
    long long i = static_cast<long long>(sqrt(n));
    return i * i == n; 
}

// từng số cũng là số chính phương
bool isPerfectSquareNum(long long n)
{
    if (n == 1 || n == 0) return true;
    return isPerfectSquare(n%10) && isPerfectSquare(n/10);
}

// trả về số chính phương nhỏ nhất có k chữ số
long long findPerfectSquare(long long k)
{
    k--;
    long long min = 1;
    while(k--) min *= 10;
    long long temp = sqrt(min);

    while(!isPerfectSquareNum(temp*temp) && temp*temp >= k)
    {
        temp++;
    }
    return (temp*temp < min*10) ?temp*temp : -1;
}



int main()
{
    int i;
    cin >> i;
    while(i--)
    {      
        long long a,b;
        cin >> a >> b;
        cout << countPerfectSquare(a,b)  << endl;
    }
}