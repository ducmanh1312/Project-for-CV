#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 
/// @note 
const int mod=1e9+7;

int calc (int N, int insert, int remove, int copy)
{

    if (N == 0)
       return 0;
    if (N == 1)
       return insert;

    int dp[N + 1];
    memset(dp, 0, sizeof(dp));
 
    dp[1] = insert;
    for (int i = 2; i <= N; i++)
    {

        if (i % 2 == 0)
            dp[i] = min(dp[i-1] + insert, dp[i/2] + copy);
 
        else
            dp[i] = min(dp[i-1] + insert, dp[(i+1)/2] + copy + remove);
    }
    return dp[N];
}

int calc (int n, int add, int dele, int copy)
{
	vector<int> vt(10005, mod);
    if (n == 0)
       return 0;
    if (n == 1)
       return add;

	for(int i=0; i<=n+1; i++)
	{
		vt[i+1] = min(vt[i+1], vt[i] + add);
		vt[2*i] = min(vt[2*i], vt[i] + copy);
		if(i > 0) vt[i-1] = min(vt[i-1], vt[i] + dele);
	}

	return vt[n-1];
}

int main(){
	//


	//
	int test;
	cin >> test;
	while(test--)
	{
        int n, x, y, z;
		cin >> n >> x >> y >> z;

		cout << calc(n,x,y,z) << endl;
	}

}