#include <bits/stdc++.h>
using namespace std;

/// @brief 
/// @bug
/// @return Đếm số lần cần thêm ít nhất để chuỗi trở nên hợp lệ

void Try(string s)
{
    stack<char> st;
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] == ')' && !st.empty() &&  st.top() == '(') 
        {
            st.pop();
 
        }
        else st.push(s[i]); 
    }
    cout << st.size() << endl;
}


int main()
{

    int test;
    cin >> test;

    while (test--)
    {
        string s;
        cin >> s;

        Try(s);
    
    }
}