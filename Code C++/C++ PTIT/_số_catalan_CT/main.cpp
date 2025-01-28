#include <bits/stdc++.h>
using namespace std;

/// @brief catalan(n) = ( 2nCn ) / (n + 1)
/// @bug
/// @return catalan(n)

unsigned long int he_so_nhi_thuc(unsigned int n, unsigned k)
{
    unsigned long int res = 1;
    if (k > n - k)
        k = n - k;
    for (int i = 0; i < k; ++i)
    {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}
unsigned long int Catalan(unsigned int n)
{
    unsigned long int c = he_so_nhi_thuc(2 * n, n);
    return c / (n + 1);
}
int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        int n;
        cin >> n;
        cout << Catalan(n) << endl;
    }
    return 0;
}