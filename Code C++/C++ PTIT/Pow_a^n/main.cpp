#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @bug

/// @return tính a^n

string s = "";
void bigPow(long long num, int n)
{
	int a[500005], maxDigit = 1;
	long long nho = 0;
	a[0] = 1;
	for (int i = 1; i <= n; i++) // duyệt các số đến n
	{
		for (int j = 0; j < maxDigit; j++) // duyệt qua các chữ số của a[]
		{
			long long temp = (a[j] * num + nho);
			a[j] = temp % 10;
			nho = temp / 10;
		}

		while (nho) // thêm nốt biến nhớ vào mảng a
		{
			a[maxDigit] = nho % 10;
			maxDigit++;
			nho /= 10;
		}
	}
	
	for (int p = maxDigit - 1; p >= 0; p--)
	{
		s += char(a[p] + '0');
	}
}

int main()
{
	int test;
	cin >> test;
	while (test--)
	{
		s = "";
		int n;
		long long num;
		cin >> num >> n;
		if (n == 0)
		{
			cout << 1 << endl;
		}
		else
		{
			bigPow(num, n);
			cout << s << endl;
		}
	}
}
