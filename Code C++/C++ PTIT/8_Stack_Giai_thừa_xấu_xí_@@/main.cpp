#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @bug
/// @return

int priority(char state)
{
    if (state == '+' || state == '-')
        return 1;
    return 2;
}

void process(char op, stack<int> &st)
{
    int l = st.top();
    st.pop();
    int r = st.top();
    st.pop();

    switch (op)
    {
    case '+':
        st.push(r + l);
        break;
    case '-':
        st.push(r - l);
        break;
    case '*':
        st.push(r * l);
        break;
    case '/':
        st.push(r / l);
        break;
    }
}

int Try(string s)
{
    stack<int> st;
    stack<char> operation;

    for (int i = 0; i < s.size(); i++)
    {
        if (isdigit(s[i]))
        {
            int temp = 0;
            while (i < s.size() && isdigit(s[i]))
            {
                temp = temp * 10 + (s[i] - '0');
                i++;
            }
            st.push(temp);
            i--;
        }
        else
        {
            while (!operation.empty() && priority(operation.top()) >= priority(s[i])) // dùng while để xứ lí hết các phép tính trước đó
            {
                process(operation.top(), st);
                operation.pop();
            }
            operation.push(s[i]);
        }
    }

    while (!operation.empty())
    {
        process(operation.top(), st);
        operation.pop();
    }

    return st.top();
}

char addOp(int i, int n)
{
    int state = (n-i) % 4;
    switch (state)
    {
    case 0:
        return '*';
        break;
    case 1:
        return '/';
        break;
    case 2:
        return '+';
        break;
    case 3:
        return '-';
        break;
    }
}

int main()
{

    int test = 1;
    cin >> test;

    while (test--)
    {
        int n;
        cin >> n;

        string s;
        for (int i = n; i >= 2; i--)
        {
            s += to_string(i);
            s += (addOp(i,n));
        }
        s += '1';


        cout << Try(s) << endl;
    }
}