#include <bits/stdc++.h>
using namespace std;

/// @brief 
/// @bug
/// @return Loại bỏ ngôi sao khỏi chuỗi 

void Try(string s)
{
    vector<char> vt;
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] == '*')
        {
            vt.pop_back();
        }else
        {
            vt.push_back(s[i]);
        }
    }

    for(int i = 0; i < vt.size(); i++)
    {
        cout << vt[i];
    }
    cout << endl;
}

int main()
{

    int test;
    cin >> test;

    while (test--)
    {
        string s;
        cin >> s;

        Try(s);
    
    }
}