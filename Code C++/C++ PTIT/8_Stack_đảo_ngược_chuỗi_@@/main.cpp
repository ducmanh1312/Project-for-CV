#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @bug
/// @return

template <typename type>
void pushA(type temp, stack<string>& st) // chèn kí tự vào stack, ghép nếu cần
{
    string s = "";
    if (!st.empty())
    {
        if (st.top() != "(")
        {
            s += st.top();
            st.pop();
        }
    }
    s += temp;
    st.push(s);
}

string uStack(string s)
{
    stack<string> st;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(') st.push("(");
        else if (s[i] == ')')
        {
            string temp = st.top();
            st.pop();
            st.pop();
            reverse(temp.begin(), temp.end());
            pushA(temp, st);
        }
        else
        {
            pushA(s[i], st);
        }
    }

    return st.top();
}

int main()
{

    int test;
    // test = 1;
    cin >> test;

    while (test--)
    {
        string s;
        cin >> s;

        cout << uStack(s) << endl;
    }
}