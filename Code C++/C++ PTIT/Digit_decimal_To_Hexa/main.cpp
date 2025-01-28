#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @param n
/// @return

string decimalToHexa(long long n)
{
    string res = "";
    if(n == 0) return "0";
    while (n > 0)
    {
        int temp = n % 16;
        n /= 16;
        res += (temp < 10 ? (char)(temp + '0') : (char)(temp - 10 + 'A'));
    }
    reverse(res.begin(), res.end());
    return res;
}

int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        long long n;
        cin >> n;
        cout << decimalToHexa(n) << endl;
    }
}
