#include <bits/stdc++.h>

using namespace std;

int main()
{
    int test;
    cin >> test;
    cin.ignore();
    while (test--)
    {
        string s;
        getline(cin, s);

        if (s[9] == '?')
        {
            if (s[8] == '2' || s[8] == '?')
            {
                s[8] = '2';
                s[9] = '3';
            }
            else
                s[9] = '9';
        }
        else if (s[8] == '?')
        {
            if (s[9] <= '3')
                s[8] = '2';
            if (s[9] > '3')
                s[8] = '1';
        }

        if (s[11] == '?')
            s[11] = '5';
        if (s[12] == '?')
            s[12] = '9';

        for (int i = 7; i <= 13; i++)
        {
            cout << s[i];
        }
        cout << endl;
    }
}
