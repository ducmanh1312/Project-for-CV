#include <bits/stdc++.h>
using namespace std;

/// @brief lưu xâu con vào array => xếp chồng
/// @bug
/// @return số phần tử của dãy con tăng dài nhất.

int binSearch(vector<int> &v, int l, int r, int key)
{
    while (r - l > 1)
    {
        int m = l + (r - l) / 2;
        if (v[m] >= key)
            r = m;
        else
            l = m;
    }
    return r;
}

int result(vector<int> &v)
{
    if (v.size() == 0)
        return 0;

    vector<int> tail(v.size(), 0);
    int length = 1;
    tail[0] = v[0];

    for (size_t i = 1; i < v.size(); i++)
    {
        if (v[i] < tail[0])
            tail[0] = v[i];
        else if (v[i] > tail[length - 1])
            tail[length++] = v[i];
        else
            tail[binSearch(tail, -1, length - 1, v[i])] = v[i];
    }

    return length;
}

int main()
{

    int test;
    cin >> test;

    while (test--)
    {
    }
}