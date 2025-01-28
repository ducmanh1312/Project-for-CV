#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @param

/// @return  tính khoảng cách hoán vị của hai hoán vị đầu vào

int check[20], n, dem;
vector<int> x, v1, v2;

void nhap()
{
	v1.clear();
	v2.clear();
	x.clear();
	cin >> n;
	int a;
	for (int i = 0; i < n; i++)
	{
		cin >> a;
		v1.push_back(a);
	}
	for (int i = 0; i < n; i++)
	{
		cin >> a;
		v2.push_back(a);
	}
	if (v1 > v2)
	{
		swap(v1, v2);
	}
}

void Try(int loop)
{
	for (int i = 1; i <= n; i++)
	{
		if (check[i] == 0)
		{
			check[i] = 1;
			x.push_back(i);
			
			if(loop == n)
			{
				if(x == v1) dem = 0;
				if(x == v2) 
				{
					cout << dem << endl;
					return;
				}
				dem++;

			}else{
				Try(loop+1);
			}

			x.pop_back();
			check[i] = 0;
		}
	}
}

int main()
{
	int tc;
	cin >> tc;
	while (tc--)
	{
		memset(check, 0, sizeof(check));
		nhap();
		Try(1);
	}
	return 0;
}