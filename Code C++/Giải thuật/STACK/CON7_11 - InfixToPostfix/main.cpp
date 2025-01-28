#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @return

int prec(char c)
{
    if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

//  convert infix expression to postfix expression
void infixToPostfix(string s)
{
    stack<char> st;
    string result;

    for (int i = 0; i < s.length(); i++)
    {
        char c = s[i];  

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') )
            result += c;
        else if (c == '(')
            st.push('(');
        else if (c == ')')
        {
            while (st.top() != '(')
            {
                result += st.top();
                st.pop();
            }
            st.pop(); // Pop '('
        }
        else // nếu là phép tính
        {
            while (!st.empty() && prec(s[i]) <= prec(st.top())) // kiểm tra ưu tiên phép tính
            {
                result += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    // Pop all the remaining elements from the stack
    while (!st.empty())
    {
        result += st.top();
        st.pop();
    }

    cout << result << endl;
}

int main()
{
    //

    //
    int test;
    cin >> test;
    while (test--)
    {
        string s;
        cin >> s;
        infixToPostfix(s);
    }
}