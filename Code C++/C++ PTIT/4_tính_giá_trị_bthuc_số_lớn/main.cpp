#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @param

/// @return

void giaithua(int n, int k)
{
    int i, j, m = 1, x[40000]; // m là số (4 chữ số) tối đa của x
    long long r = 0, s;
    x[0] = 1;
    for (i = n - k + 1; i <= n; i++) // Nhân x với 
    {
        for (j = 0; j < m; j++)
        {
            s = x[j] * i + r;
            x[j] = s % 10000;
            r = s / 10000;
        }
        while (r > 0)
        {
            x[m++] = r % 10000;
            r /= 10000;
        }
    }

    for (i = m - 1; i >= 0; i--) // In ra các số 0 của cụm 4 số (trừ vị trí đầu tiên)
    {
        if (i < m - 1 && x[i] < 1000)
            cout << "0";
        if (i < m - 1 && x[i] < 100)
            cout << "0";
        if (i < m - 1 && x[i] < 10)
            cout << "0";
        cout << x[i];
    }
    cout << endl;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        giaithua(n, k);
    }
}