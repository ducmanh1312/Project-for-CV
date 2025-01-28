#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @bug
/// @return số lần chèn abc vào xâu để tạo ra xâu kết quả

bool Try(string s)
{
    stack<char> st;
    for (int i = 0; i < s.size(); i++)
    {
        if ((st.empty() || s[i] != st.top()) && st.size() < s.size())
        {

            st.push('c');
            st.push('b');
            st.push('a');
            i--;
        }
        else  st.pop();
    }

    return st.empty();
}

int main()
{

    int test;
    cin >> test;

    while (test--)
    {
        string s;
        cin >> s;

        cout << Try(s) << endl;
    }
}