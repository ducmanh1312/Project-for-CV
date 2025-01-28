#include <bits/stdc++.h>
using namespace std;

int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        int n;
        float x;
        cin >> n >> x;

        float sum = 0;

        for (int k = 1; k <= n; k++)
        {
            float tu = pow(x, k);
            float mau = 0;

            for (int i = 1; i <= k; i++)
            {
                mau += i;
            }

            float temp = tu / mau;
            sum += temp;
        }
        cout << fixed << setprecision(3) << sum  << endl;

    }
}
