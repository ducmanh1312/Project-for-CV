#include <bits/stdc++.h>
using namespace std;

/// @brief 
/// @bug
/// @return ngoặc  hợp lệ

bool check( string s)
{
    stack<char> st;
    for(char c: s)
    {
        if( c == '(' ||  c == '{' ||  c == '[' ) st.push(c);
        else
        {
            if(st.empty()) return false;
            char temp = st.top();
            if(c == ')' && temp != '(') return false;
            if(c == '}' && temp != '{') return false;
            if(c == ']' && temp != '[') return false;
            st.pop();
        }
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
        cout << check(s) << endl;
    
    }
}