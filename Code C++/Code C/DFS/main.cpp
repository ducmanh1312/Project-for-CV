#include <iostream>
#include <stdio.h>
#include <queue>
#include <string>
#include <vector>
#include <set>
#include <stack>
using namespace std;

#include <algorithm>

bool checkDFS(int n, std::vector<std::vector<int>> e, int u, int v)
{
    stack<int> st;
    int b[1001] = {0};
    st.push(u);
    b[u] = 1;

    while (!st.empty())
    {
        int x = st.top();
        bool next = false;
        for (int i = 0; i < e.size(); i++)
        {
            if (x == e[i][0] && b[e[i][1]] == 0)
            {
                next = true;
                b[e[i][1]] = 1;
                st.push(e[i][1]);
                if (e[i][1] == v)
                    return true;
            }
            if (!next)
                st.pop();
        }
    }
    return false;
}

class Solution
{
public:
    bool a[1001][1001]; // đường đi giữa các đỉnh
    int graphFunction(int n, std::vector<std::vector<int>> e, int u, int v)
    {
        set<int> s;
        bool b[10001]; // kt đỉnh chưa đi qua - true
        int c[10001];  // kt số đỉnh đã đi qua trên đường
        bool kt = false;
        for (int i = 0; i <= n; i++)
        {
            b[i] = true;
            c[i] = 0;
        }
        for (int i = 0; i < e.size(); i++)
        {
            a[e[i][0]][e[i][1]] = true;
            a[e[i][1]][e[i][0]] = true;
        }

        queue<int> q;
        q.push(u);
        b[u] = false;

        while (!q.empty())
        {
            int k = q.front();
            for (int i = 0; i <= n; i++)
            {
                if (a[k][i] && b[i])
                {
                    c[i] = c[k] + 1;
                    if (i == v)
                    {
                        s.insert(c[v]);
                        a[k][i] = false;
                    }
                    else
                    {
                        q.push(i);
                        b[i] = false;
                        
                    }
                }
            }
            q.pop();
        }
        return (!s.empty()) ? -1 : *s.end();
    }

}

int
graphFunction(int n, std::vector<std::vector<int>> e, int u, int v)
{
    bool b[10001];      // kt đỉnh chưa đi qua - true
    int c[10001];       // kt số đỉnh đã đi qua trên đường
    bool a[1001][1001]; // đường đi giữa các đỉnh
    bool kt = false;
    for (int i = 0; i <= n; i++)
    {
        b[i] = true;
        c[i] = 0;
    }
    for (int i = 0; i < e.size(); i++)
    {
        a[e[i][0]][e[i][1]] = true;
        a[e[i][1]][e[i][0]] = true;
    }

    queue<int> q;
    q.push(u);
    b[u] = false;

    while (!q.empty())
    {
        int k = q.front();
        for (int i = 0; i <= n; i++)
        {
            if (a[k][i] && b[i])
            {
                q.push(i);
                b[i] = false;
                c[i] = c[k] + 1;
                if (i == v)
                    break;
            }
        }
        q.pop();
    }
    return (c[v] == 0) ? -1 : c[v];
}

int main()
{
    int n = 6;
    vector<std::vector<int>> e = [ [ 1, 3 ], [ 1, 2 ], [ 2, 3 ], [ 3, 4 ], [ 2, 5 ], [ 4, 6 ], [ 6, 5 ], [ 4, 5 ] ];
    int u = 1, v = 5;
    cout << graphFunction(n, e, u, v);
}
