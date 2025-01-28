#include <bits/stdc++.h>
using namespace std;

bool isPerfectSquare(long long n)
{
    long long i = static_cast<long long>(sqrt(n));
    return i * i == n;
}

bool isFibonacci(long long n)
{
    return isPerfectSquare(5 * n * n + 4) || isPerfectSquare(5 * n * n - 4);
}

// Hàm tìm n! min có k chữ số
long long fibonacciMin(long long n)
{
    while (isFibonacci(++n) == 1);
    return n;
}

int main()
{
    int i;
    cin >> i;
    while (i--)
    {
        long n;
        cin >> n;
        cout << fibonacciMin(n) << endl;
    }
}
