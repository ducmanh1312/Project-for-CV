#include <bits/stdc++.h>
using namespace std;

/// @brief 
/// @bug
/// @return 

int result(int k, int s)
{
    int count = 0;
    if(s == 3*k) return 1;
    for(int i = 0; i <= k; i++)
    {
        for(int j = 0; j <= min(k, s-i); j++)
        {
            int n = s - i - j;
            if(n <= k ) count++;
        }
    }
    return count;
}

int main()
{

    int test;
    cin >> test;

    while (test--)
    {
        int k,s;
        cin >> k >> s;
        cout << result(k,s) << endl;
    }
}