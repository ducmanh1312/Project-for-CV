#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 
/// @note 

int calc(int arr[], int n)
{
	int ans[n];
	for(int i=0; i<n; i++)
	{
		ans[i] = arr[i];
        for(int j=0; j < i-1; j++)
        {
                ans[i] = max(ans[i], ans[j] + arr[i]);
        }
	}
	return *max_element(ans, ans+n);
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
		int arr[N];
		for(int i = 0; i < N; i++)
		    cin >> arr[i];
		
		cout << calc(arr,N) << endl;
	}

}