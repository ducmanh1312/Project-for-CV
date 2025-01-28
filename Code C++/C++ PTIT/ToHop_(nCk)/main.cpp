// Tính số dư tổ hợp chập k của n khi chia cho m
#include <bits/stdc++.h>
using namespace std;

int C(int n, int k)
{
    if (k > n - k) k = n-k;
    int C[k+1];
    memset(C, 0, sizeof(C));

    C[0] = 1;
    for(int i = 1; i <= n; i++)
    {
        for(int j = k; j > 0; j--)
        {
            C[j] = (C[j] + C[j-1]) ;
        }
    }
    return C[k];
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int k, n;
        cin >> n >> k ;
        cout << C(n, k) << endl;
    }
    return 0;
}