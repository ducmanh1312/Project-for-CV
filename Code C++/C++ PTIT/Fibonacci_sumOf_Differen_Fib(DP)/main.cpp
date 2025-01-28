#include <bits/stdc++.h>
using namespace std;

/// @brief tính hết các kết quả ra rồi in 1 thể
/// @bug

/// @return đếm số cách biểu diễn số N thành tổng của các số Fibonacci không lặp lại

int a[30], dp[105][100005];

void fibonaci()
{
    a[1] = 1, a[2] = 2;
    for (int i = 3; i <= 25; ++i)
    {
        a[i] = a[i - 1] + a[i - 2];
    }   
}

int Try()
{
//
	for(int i = 0; i <= 25; i++)
	{
		dp[i][0] = 1;
	}
	dp[1][1] = 1;
	
//
	for(int stt = 2; stt <= 25; stt++)
	{
		for(int sum = 0; sum <= 100000; sum++)
		{
			if(sum >= a[stt])
			{
				dp[stt][sum] = dp[stt-1][ sum- a[stt] ] + dp[stt-1][sum];
			}
			else dp[stt][sum] = dp[stt-1][sum];
		}
	}
}

int main()
{
	fibonaci();
	Try();
    
    int t;
    cin >> t;
    while (t--)
    {
    	int n;
        cin >> n;
        cout << dp[25][n]  << endl;
    }
    return 0;
}