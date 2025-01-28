#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @return đưa về cơ số 10 => tính tổng => đưa lại về cơ số K
/// @note

#define ll long long
int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		ll k, tmp = 1, num1 = 0, num2 = 0;
		string a, b, res = "";
		cin >> k >> a >> b;
		
		for (int i = a.size() - 1; i >= 0; i--)
		{
			num1 += tmp * (a[i] - '0');
			tmp *= k;
		}
		tmp = 1;
		for (int i = b.size() - 1; i >= 0; i--)
		{
			num2 += tmp * (b[i] - '0');
			tmp *= k;
		}
		ll num = num1 + num2;
		
		while (num > 0)
		{
			ll tmp1 = num % k;
			num /= k;
			char s = tmp1 + '0';
			res = s + res;
		}

		cout << res << endl;
	}
}