#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 
/// @note 
const int mod=1e9+7;

int calc(int m, int n)
{
	vector<vector<int>> vt(m+1, vector<int>(n+1, 0));
	for(int i=0; i<=m; i++)
	{
		for(int j=0; j<=n; j++)
		{
			if(i == 0 && j == 0) vt[i][j] = 0;
			else if(i == 0 && j != 0 || j == 0 && i != 0) vt[i][j] = 1;
			else vt[i][j] = (vt[i-1][j] + vt[i][j-1]);
		}
	}
	return vt[m][n];
}

int main(){
	//

	//
	int test;
	cin >> test;
	while(test--)
	{
        int m, n;
		cin >> m >> n;
		
		cout << calc(m, n) << endl;
	}

}