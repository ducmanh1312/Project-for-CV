#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 
/// @note 
const int mod=1e9+7;

int calc (string s)
{
	string r = s;
	reverse(r.begin(), r.end());
	int n = s.size();
	
	int dp[n+1][n+1];
	memset(dp, 0, sizeof(dp));

	int ans = 0;
	for(int i=0; i<=n; i++)
    {
		for(int j=0; j<=n; j++)
		{
			if(i == 0 || j == 0) dp[i][j] = 0;
			else if(s[i] == r[j]) 
			{
				dp[i][j] = dp[i-1][j-1] + 1;
				ans = max(ans, dp[i][j]);
			}
			else dp[i][j] = 0;
		}
	}
	return ans;
}

int main(){
	//


	//
	int test;
	cin >> test;
	while(test--)
	{
        string s;
		cin >> s;

		cout << calc(s) << endl;
	}

}