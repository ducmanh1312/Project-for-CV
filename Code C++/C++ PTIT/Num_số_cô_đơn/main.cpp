#include <bits/stdc++.h>
using namespace std;

/// @brief 
/// @bug
/// @return 


int main()
{

    int test;
    cin >> test;

    while (test--)
    {
        long n;
        cin >> n;
        vector<long> a(1000005,0);
        long res = 0;
        for(long i = 0; i < n; i++)
        {
            long x;
            cin >> x;

            if(a[x] == 1)
            {
                a[x]++;
                res--;
            }
            if(a[x] == 0) 
            {
                a[x]++;
                res++;
            }
        }
        cout << res <<endl;
    }
}