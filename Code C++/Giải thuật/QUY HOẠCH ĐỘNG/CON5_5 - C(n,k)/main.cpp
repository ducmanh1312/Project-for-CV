#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 
/// @note 
const int mod=1e9+7;

int main(){
	//

	//
	int test;
	cin >> test;
	while(test--)
	{
        int n, k;
		cin >> n >> k;
		

		int C[k+1];
		memset(C, 0, sizeof(C));

		C[0] = 1;
		for(int i = 1; i <= n; i++)
		{
			for(int j = k; j > 0; j--)
			{
				C[j] = (C[j] + C[j-1]) % mod;
			}
		}
		cout << C[k] << endl;
	}

}