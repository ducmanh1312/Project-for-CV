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
        int n;
		cin >> n;
		
		vector<int> v(n+1, 0);
		v[0] = 1;

		for(int i=1; i<=2*n; i++)
		{
			for(int j = n; j>0; j--)
				v[j] = v[j] + v[j - 1];
		}

		cout << v[n] / (n+1) << endl;		
	}

}