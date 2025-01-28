#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long n;
        cin >> n;
        if (n % 2 == 0)
        {
            cout << pow(10,n/2) - pow(10,n/2 - 1) << endl;
        }
        else
        {
            long long x = (n-1)/2;
            cout << (pow(10,x) - pow(10, x -1))*10 << endl;
        }
    }
}