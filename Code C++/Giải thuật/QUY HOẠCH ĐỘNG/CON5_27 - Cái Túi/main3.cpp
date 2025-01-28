#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @return
/// @note



int knapsack(vector<vector<int>> &dp, int W[], int C[], int n, int w)
{
	// dk dung
	if (n == 0 || w == 0)
        return 0;

	// return existing result
    if (dp[n][w] != 0)
        return dp[n][w];

    if (W[n-1] <= w)
        return dp[n][w] = max(C[n - 1] + knapsack(dp, W, C, n - 1, w - W[n - 1]), knapsack(dp, W, C, n - 1, w));
    else
        return dp[n][w] = knapsack(dp, W, C, n - 1, w);
}

int main()
{
	//

	//
	int test;
	cin >> test;
	while (test--)
	{
		int n, w;
		cin >> n >> w;
		int W[n], C[n];
		for (int i = 0; i < n; i++)
			cin >> W[i];
		for (int i = 0; i < n; i++)
			cin >> C[i];

		// init
		vector<vector<int>> dp(n+1, vector<int>(w + 1, 0));

		cout << knapsack(dp, W, C, n, w) << endl;
	}
}