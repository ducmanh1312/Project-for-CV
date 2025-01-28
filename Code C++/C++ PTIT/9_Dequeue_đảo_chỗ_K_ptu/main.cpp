#include <bits/stdc++.h>
using namespace std;

/// @brief 
/// @bug
/// @return Đảo chỗ K phần tử trong hàng đợi



void Try(string s, int k)
{
    stringstream ss(s);
    string temp;
    deque<string> res;
    int i = 0;
    
    while(getline(ss, temp, ','))
    {
        if(i < k) 
        {
            i++;
            res.push_front(temp);
        }else
        {
            res.push_back(temp);
        }
    }

    for(int i = 0; i < res.size(); i++)
    {
        cout << res[i];
        if(i != res.size()-1) cout << ',';
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
        int k;
        cin >> s >> k;

        Try(s, k);
    }
}