#include <bits/stdc++.h>
using namespace std;

/// @brief dùng loang
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
    
	//
	for(int i = 0; i <= 25; i++)
	{
		dp[i][0] = 1;
	}
	dp[1][1] = 1;
}

int Try(int stt, int n)
{	
	if(dp[stt][n]) return dp[stt][n];
	
	if(stt <= 25 && n <= 100000 && n >= a[stt])
	{
		dp[stt][n] = Try(stt-1, n - a[stt]) + Try(stt-1, n );
	}
	else dp[stt][n] = Try(stt-1, n );
	
	return dp[stt][n];
}

int main()
{
	fibonaci();
	Try(2, 0);
    
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