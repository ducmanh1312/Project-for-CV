#include <bits/stdc++.h>
using namespace std;

/// @brief tách chuỗi bằng stringstream
/// @bug 
/// @return

string Try(string s)
{
    deque<string> vt;
    stringstream ss(s);
    string temp;
    
    while(getline(ss, temp, '/'))
    {
        if(temp == "" || temp == "." )
            continue;
        else if(temp == ".." )
        {
            if(!vt.empty())  vt.pop_back();
        }
        else 
        {
            vt.push_back(temp);
        }
    }

    string res = "";
    for(auto c : vt)
    {
        res += "/" + c;
    }
    return ((res == "") ?"/" :res);
}

int main()
{

    int test = 1;
    cin >> test;

    while (test--)
    {
        string s;
        cin >> s;
        cout <<Try(s) << endl;
    }
}