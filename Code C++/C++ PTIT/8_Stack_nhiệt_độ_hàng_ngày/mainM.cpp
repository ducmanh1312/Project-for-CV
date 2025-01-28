#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @bug
/// @return

#define int long long

vector<int> calc(string s)
{
    vector<int> vt;
// tách xâu
    stringstream ss(s);
    string temp;
    while(getline(ss, temp, ','))
    {
        vt.push_back(stoi(temp));
    }

// xử lí
    stack<int> dq; // chứa vị trí trong vt
    vector<int> res(vt.size(),0);
    for(int i = 0; i < vt.size(); i++)
    {
        // xử lí
        while(!dq.empty() && vt[i] > vt[dq.top()])
        {
            res[dq.top()] = i - dq.top();
            dq.pop(); 
        }
        //
        dq.push(i);
    }

    return res;
}

int32_t main()
{
    int t;
    cin >> t;
    while (t--)
    {
        string s;
        cin >> s;

        vector<int> res = calc(s);
        for(int i = 0; i < res.size(); i++)
        {
            cout << res[i] << ((i != res.size() - 1) ?"," :"") ;
        }
        cout << endl;
    }
}

// << (i != res.size()-1) ?',' :' '