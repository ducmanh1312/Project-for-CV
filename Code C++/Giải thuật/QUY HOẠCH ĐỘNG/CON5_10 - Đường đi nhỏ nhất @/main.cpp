#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 
/// @note 

int calc(int a[][1005], int n, int m)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
        {
			if(i == 0) a[0][j] += a[0][j-1];
			else if(j == 0) a[i][0] += a[i-1][0];
            else a[i][j] += min({a[i-1][j], a[i][j-1], a[i-1][j-1]});
        }
	}
	return a[n-1][m-1];
}

int main(){
	//

	//
	int test;
	cin >> test;
	while(test--)
	{
        int m, n;
		cin >> n >> m;
		int a[n][1005];
		for(int i = 0; i < n; i++)
		{
			for(int j =0; j < m; j++)
			{
				cin >> a[i][j];
			}
		}

		cout << calc(a,n,m) << endl;
		
	}

}