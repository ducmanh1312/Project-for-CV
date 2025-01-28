#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @bug
/// @return loại bỏ các bản sao bao gồm việc chọn hai chữ cái liền kề từ trái -> phải đến khi chúng ta không thể tiếp tục nữa

void count(string s)
{
    deque<char> st;

    for (int i = 0; i < s.size(); i++)
    {
        if (!st.empty() && s[i] == st.back())
            st.pop_back();
        else
        {
            st.push_back(s[i]);
        }
    }

    string res(st.begin(), st.end());
    cout << res << endl;
}

int main()
{

    int test;
    cin >> test;

    while (test--)
    {
        string s;
        cin >> s;

        count(s);
    }
}