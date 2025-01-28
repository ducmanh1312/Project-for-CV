#include <iostream>
#include <stdio.h>
#include <queue>
#include <string>
#include <vector>
#include <set>
#include <stack>
using namespace std;

#include <algorithm>

int main()
{
    queue<int> q;
    int b[1001] = {};
    int a[1001];
    int temp;
    int n, k;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    cin >> k;

    for (int i = 0; i < n; i++)
    {
        if (!b[a[i]])
        {
            if (q.size() < k)
            {
                b[a[i]] = 1;
                q.push(a[i]);
            }
            else
            {
                b[a[i]] = 1;
                q.push(a[i]);
                q.pop();
            }
        }
    }
    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
}

/*
    string output = String.substr(0, String.length()/2)

    for(int x: $array )

    set<vector<int>> st;

    sort(arr.begin(),arr.end()); // thay đổi arr gốc

    reverse(String.begin(),String.end()); // thay đổi string gốc
    String.erase(input.length()-1,1); // thay đổi string gốc

    template <class val>
    void swapVal(val &a , val &b)
*/