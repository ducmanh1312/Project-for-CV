#include <bits/stdc++.h>
using namespace std;


string multi(string res, string num) // dao chuoi
{
	// khai bao
	int n = res.size();
	int m = num.size();
	string anser(n + m,'0');
	
	// 
	for(int i = n - 1; i >= 0; i--)
	{
		int nho = 0; // Reset bien nho
		
		for(int j = m - 1; j >= 0; j--)
		{
			int tmp = (res[i] - '0') * (num[j] - '0') + (anser[i + j + 1] - '0') + nho;
			anser[i + j + 1] = (tmp % 10 + '0');
			nho = tmp / 10;
		}
		//
		anser[i] += nho;
	}
	
	long long pos = anser.find_first_not_of('0');    
	if(pos != string::npos)
	{
		return anser.substr(pos);
	}
	
	return 0;
}

string factorial(int n)
{
	string res = "1";
	for(int i = 2; i <= n; i++)
	{
		res = multi(res, to_string(i));
	}
	
	return res;
}

int main()
{
	int test = 1;
	cin >> test;
	while(test--)
	{
		int n;
		cin >> n;
		cout << factorial(n) << endl;
	}
}