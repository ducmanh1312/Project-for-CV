#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 
/// @note 

int dp(int a[], int N)
{
	int sum[N]; 
	sum[0] = a[0];

	for(int i=1; i<N; i++)
	{
		sum[i] = a[i];
		for(int j=0; j<i; j++)
		
		{
			if(a[j] < a[i] && sum[j]+a[i] > sum[i])
			{
				sum[i] = sum[j]+a[i]; 
			}
		}

	}
	return *max_element(sum, sum+N);
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
		int a[N];
		for(int i = 0; i < N; i++)
		{
			cin >> a[i];
		}

		cout << dp(a,N) << endl;
		
	}

}