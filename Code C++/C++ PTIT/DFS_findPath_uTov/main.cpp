#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @param n
/// @return

// DFS khu de quy va hoat dong theo trinh tu giong nhu de quy.
bool check[100001];

bool findPath(int n, vector<vector<int>> edges, int u, int v)
{
    if (u == v)
        return true;
    stack<int> st;
    int s = edges.size();
    st.push(u);
    check[u] = true;

    while (!st.empty())
    {
        int top = st.top(), stsize = st.size();
        for (int i = 0; i < s; ++i)
        {
            vector<int> &edge = edges[i];
            int &f = edge[0], &t = edge[1];
            if (f != top || check[t])
                continue;
            if (t == v)
                return true;
            check[t] = true;
            st.push(t);
            break;
        }
        if (stsize == st.size())
            st.pop();
    }
    return false;
}

int main()
{
    int test;
    cin >> test;
    while (test--)
    {
    }
}
