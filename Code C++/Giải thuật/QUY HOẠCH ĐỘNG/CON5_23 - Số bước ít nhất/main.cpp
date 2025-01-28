#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @return = số phần tử ít nhất cần xóa =  n - (xâu con tăng dài nhất)
/// @note
const int mod = 1e9 + 7;

int calc(int a[], int n)
{
	vector<int> res(n+1,1);

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < i; j++)
			if(a[i] >= a[j]) res[i] = max(res[i], res[j]+1);
	}
	return n - *max_element(res.begin(),res.end());
}

int main()
{
	//

	//
	int test;
	cin >> test;
	while (test--)
	{
		int n;
		cin >> n;
		int a[n];
		for (int i = 0; i < n; i++)
		{
			cin >> a[i];
		}

		cout << calc(a, n) << endl;
	}
}