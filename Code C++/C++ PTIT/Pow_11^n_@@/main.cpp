#include <bits/stdc++.h>
using namespace std;


/// @brief Dùng tính chất đặc biệt
/// @param n 
/// @result Code tính 11^n


void lon_hon_9(int n, bool mot = 1)
{
    if (n > 9)
    {
        cout << "123456790";
        lon_hon_9(n - 9, 0);
        cout << "098765432";
        if (mot)
            cout << '1';
    }
    else
    {
        if (n == 1)   return;
        for (int i = 1; i <= n; i++)
        {
            cout << i;
        }
        for (int i = n - 1; i > 1; i--)
        {
            cout << i;
        }
        return;
    }
}

void nho_hon_9(int n)
{
    if (n == 1)
    {
        cout << 11;
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        cout << i;
    }
    for (int i = n - 1; i > 0; i--)
    {
        cout << i;
    }
    return;
}


int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        int n;
        cin >> n;
        if (n > 9)
            lon_hon_9(n);
        else
            nho_hon_9(n);
        cout << endl;
    }
    return 0;
}