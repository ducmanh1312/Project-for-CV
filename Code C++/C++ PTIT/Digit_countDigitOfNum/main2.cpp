#include <bits/stdc++.h>

using namespace std;



int main()
{
    int test;
    cin >> test;
    while(test--)
    {
        string s;
        cin >> s;
        if(s[0] == '-') s.erase(0,1);

        cout << s.size() << endl;
    }
}
