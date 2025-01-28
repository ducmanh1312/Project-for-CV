#include <bits/stdc++.h>
using namespace std;


string s[100005];
// Hàm tạo xâu giai thừa lưu vào s
void giaithua(int n)
{
	int a[500005], maxDigit = 1;
	int nho = 0;
	a[0] = 1;
	for (int i = 2; i <= n; i++) // duyệt các số đến n
	{
		for (int j = 0; j < maxDigit; j++) // duyệt qua các chữ số của a[]
		{
			int temp = (a[j] * i + nho);
			a[j] = temp % 10;
			nho = temp / 10;
		}

		while (nho) // thêm nốt biến nhớ vào mảng a
		{
			a[maxDigit] = nho % 10;
			maxDigit++;
			nho /= 10;
		}
		
		for (int p = maxDigit - 1; p >= 0; p--)
		{
			s[i] += char(a[p] + '0');
		}
	}
}


int main()
{
	giaithua(10005);
	int tc;
	cin >> tc;

	while (tc--)
	{
		int n;
		cin >> n;
		if (n == 0 || n == 1)
		{
			cout << "1";
		}
		else
		{
			cout << s[n];
		}
		cout << endl;
	}
}