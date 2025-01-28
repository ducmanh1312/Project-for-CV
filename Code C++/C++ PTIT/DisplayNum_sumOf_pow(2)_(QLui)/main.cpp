#include <bits/stdc++.h>
using namespace std;

/// @brief  số cách biểu diễn Nthành tổng của các số luỹ thừa của 2, không tính hoán vị, có lặp
/// @bug
/// @return 

int Try(int n, int k) // k : số mũ lớn nhất của 2^k đc dùng 
{
	if(n == 0 || k == 0) return 1; // if k = 0 để tính nhanh hơn

	int res = 0;
	for(int i = 0; i <= k; i++)
	{
		if(n >= pow(2,i)) res += Try(n - pow(2,i) , i);
	}
	return res;

}

int main()
{
	int test = 1;
	cin >> test;

	while(test--)
	{
		int N;
		cin >> N;
		
		if(N > 0) cout << Try(N,log2(N)) << endl;
	}
}