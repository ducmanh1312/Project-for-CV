#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @bug
/// @return

int xapxep(string a, string b) // a > b
{
    if (a == b)
        return 0;

    if (a[0] != '-' && b[0] != '-' && a.compare(b) > 0)
        return 1;
    if (a[0] == '-' && b[0] == '-' && a.compare(b) < 0)
        return 1;
    if (a[0] != '-' && b[0] == '-')
        return 1;

    return -1;
}

void Try(string s, int k)
{
    stringstream ss(s);
    string temp;
    int tmp;
    deque<int> dq;
    vector<int> res(1, 0);

    while (getline(ss, temp, ','))
    {
        stringstream st(temp);
        st >> tmp;
        res.push_back(tmp);
    }

    for (int i = 1; i < res.size(); i++)
    {
        while (!dq.empty() && res[dq.back()] <= res[i])
        {
            dq.pop_back();
        }

        while (!dq.empty() && dq.front() < i - k + 1)
        {
            dq.pop_front();
        }

        dq.push_back(i);

        if (i >= k)
            cout << res[dq.front()] << ((i != res.size() - 1) ? "," : "");
    }
    cout << endl;
}

int main()
{

    int test;
    cin >> test;

    while (test--)
    {
        string s, ss;
        int k;
        cin >> s >> k;

        Try(s, k);
    }
}