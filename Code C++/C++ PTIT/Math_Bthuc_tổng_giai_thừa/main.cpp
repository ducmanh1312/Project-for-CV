#include <bits/stdc++.h>
using namespace std;

int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        int i = 1,n;
        float x, S = 0, T = 1;
        long long M = 1;

        cin >> n >> x;

        while( i <= n)
        {
            T = T * x;
            M = M * i;
            S += T/M;
            i++;
        }
         cout << fixed << setprecision(3) << S << " " << endl;
    }
}
