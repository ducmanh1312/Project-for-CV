#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @param n
/// @return
long long duyet(long long a[], long long n)
{
    long long x = a[1] - a[0];
    int y = 0;
    for (int i = 1; i < n - 1; i++)
    {
        if ((a[i + 1] - a[i]) != x)
        {
            y = 1;
            break;
        }
    }
    
    if (y == 1)
    {
        cout << "NO" << endl;
    }
    else
        cout << "YES" << endl;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long n;
        cin >> n;
        long long a[n];
        for (int j = 0; j < n; j++)
        {
            cin >> a[j];

        }
        duyet(a, n);
    }
    return 0;
}