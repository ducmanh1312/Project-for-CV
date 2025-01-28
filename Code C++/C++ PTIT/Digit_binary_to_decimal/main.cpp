#include <bits/stdc++.h>
using namespace std;

/// @brief 
/// @param n 
/// @return 

long long binaryToDecimal(string s)
{
    reverse(s.begin(), s.end());
    long long a = 1;
    long long res = 0;
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] == '1') res += a;
        a*=2;
    }
    return res;
}

int main()
{
    int test;
    cin >> test;
    while(test--)
    {
        string s;
        cin >> s;
        cout << binaryToDecimal(s) << endl;
    }
}
