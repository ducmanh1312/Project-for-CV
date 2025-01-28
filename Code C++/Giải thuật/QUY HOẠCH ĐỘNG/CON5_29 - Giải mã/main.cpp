#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 
/// @note 

int calc(string s, int n)
{
	int dp[1005] = {};
	dp[0] = 1;
	dp[1] = 1;

	for(int i=2; i<=n; i++)
	{
		if(s[i-1] != '0') dp[i] = dp[i-1];
		if(s[i-2] == '1' || (s[i-2] == '2' && s[i-1] <= '6')) dp[i] += dp[i-2];
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
		string s;
		cin >> s;


		cout << calc(s, s.size()) << endl;
		
	}

}