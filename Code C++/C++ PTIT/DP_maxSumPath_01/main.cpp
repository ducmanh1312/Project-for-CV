#include <bits/stdc++.h>
using namespace std;

/// @brief 
/// @return trả về hiệu số bit 0 và 1 lớn nhất của xâu con
int main()
{
	int test;
	cin >> test;
	while (test--)
	{
		string s;
		cin >> s;
		int kiluc = 0;
		int sum = 0;
		bool check = true;
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] == '0')
			{
				sum++;
				check = false;
			}
			else
			{
				if (sum != 0) // Trừ sum đến min = 0
				{
					sum--;
				}
			}
			if (sum > kiluc)
			{
				kiluc = sum;
			}
		}
		if(check) kiluc = -1;
		cout << kiluc << endl;
	}
	return 0;
}