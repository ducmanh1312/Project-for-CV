#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @bug
/// @return số dãy nhị phân nằm giữa hai dãy nhị phân n phần tử x và y cho trước.

#define ull long long // bắt buộc 
ull change(string s, int n)
{
	ull res = 0;
	reverse(s.begin(), s.end());
	for(int i = 0; i < n; i++)
	{
		if(s[i] == '1')
			res |= 1 << i;
	}
	return res;
}
int main()
{
    int tc;
    cin >> tc;
    while (tc--)
    {
        int n;
        cin >> n;
        string s, t;
        cin >> s >> t;
        
        ull x = change(s, n);
        ull y = change(t, n);
        if (x > y)
        {
            cout << x - y - 1;
        }
        else if (x < y)
        {
            cout << y - x - 1;
        }
        else
        {
            cout << 0;
        }
        cout << endl;
    }
    return 0;
}