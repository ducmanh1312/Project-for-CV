#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @return

int main()
{
    //

    //
    string s;
    deque<int> st;

    while (cin >> s)
    {
        if (s == "PUSH")
        {
            int n;
            cin >> n;
            st.push_back(n);
        }
        else if (s == "POP")
        {
            {
                if (!st.empty())
                    st.pop_back();
            }
        }
        else if (s == "PRINT")
        {
            if (st.empty())
                cout << "NONE" << endl;
            else
            {
                // while(!st.empty())
                // {
                //     cout << st.front() << " ";
                //     st.pop_front();
                // }
                cout << st.back() << endl;
            }
        }
    }
    return 0;
}