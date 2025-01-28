#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @bug 
/// @return  Số cách biểu diễn N thành tổng của các số chính phương khác không, không tính hoán vị, có lặp

int Try(int N, int x) // x^2 
{
	// Đk dừng
	if(N == 0 || x == 1) return 1; 
	
	// 
	int res = 0;
	for(int i = 1; i <= x; i++)
	{
		if(N >= pow(i,2)) res += Try(N-pow(i,2), i );
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
		
		if(N > 0)
			cout << Try(N,sqrt(N) )<< endl;
	}
}