#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 
/// @note 

int Try(int n)
{
	vector<int> dp(n+1,0);
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 3;

	for(int i = 4; i <= n; i++)
	{
		dp[i] = i;
        for (int x = 1; x <= ceil(sqrt(i)); x++) 
        {
            int temp = x*x;
            if (temp <= i)
                dp[i] = min(dp[i], 1 + dp[i - temp]);
        }
	}

	return dp[n];
}

int main(){
	//

	//
	int test;
	cin >> test;
	while(test--)
	{
        int N;
		cin >> N;
		cout << Try(N) << endl;
	}

}