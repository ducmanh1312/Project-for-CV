#include <bits/stdc++.h>

using namespace std;



//  True <=> tích các ước nguyên tố của n bằng n
bool productOfPrimeFactors(long long n)
{
    if (n < 2)
        return false;
    for (long long i = 2; i * i <= n; i++)
    {
        if (n % i == 0 && n % (i * i) == 0)
            return true;
    }
    return false;
}

int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        long long n;
        cin >> n;

        if (n < 2)
        {
            cout << "NO" << endl;
        }
        else
        {
            bool result = productOfPrimeFactors(n);
            if (result)
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}
