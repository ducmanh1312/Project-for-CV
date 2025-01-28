// 
// IN:
// OUT: 
#include <iostream>
#include <cmath>
#define FOR(i, start, end) for (int i = start; i <= end; i++)

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;

    if (k != 0, n % (2 * k) != 0)
    {
        cout << -1;
        return 0;
    }

    if (k == 0)
    {
        FOR(i, 1, n)
            cout << i << " ";
    }
    else
    {
        int a[n+1];
        FOR(i, 1, n){
            a[i] = i;
        }
        int sz = n % (2*k);
    }
}
