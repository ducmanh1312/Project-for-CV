#include <bits/stdc++.h>
using namespace std;

/// @brief số cách biểu diễn N thành tổng của các số tự nhiên khác không và nhỏ hơn N
/// @bug
/// @return arr[i] = arr[i] + arr[i - row] với i >= row
const long long mod = 1e9 + 7;

long long calc(long long n)
{
    //
    long long res = 0;
    long long arr[n+3]; // arr[n] lưu số cách biểu diễn số n thành tổng 
    memset(arr, 0, sizeof(arr));
    arr[0] = 1;

    
    for(int num = 1; num <=  n - 1; num++) // num < n
    {
        for(int d = 0; d <= n - num; d++) 
        {
                arr[num + d] += arr[d];
                arr[num + d] %= mod;
        }
    }

    return arr[n];
}

int main()
{

    int test;
    cin >> test;

    while (test--)
    {
        long n;
        cin >> n;
        cout << calc(n) << endl;
    }
}