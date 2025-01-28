#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @bug
/// @return độ dài chuỗi con dài nhất bao gồm các ký tự khác nhau và sắp xếp theo thứ tự từ điển

void find(string s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    vector<int> count(s.size(), 1);
    for (int i = 1; i < s.size(); i++)
    {
        for (int j = i-1; j >= 0; j--)
        {
            if (s[i] > s[j])
            {
                count[i] = max(count[i], count[j]+1);
            }
        }  
    }
    int x = *max_element(count.begin(), count.end());

    cout << x << endl;
}

int main()
{

    int test;
    cin >> test;

    while (test--)
    {
        string s;
        cin >> s;
        find(s);
    }
}
