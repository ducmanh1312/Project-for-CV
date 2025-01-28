#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 
/// @note 

int N,S;

bool Try(int a[], int pos, int s)
{
	//
	if(s == S) return true;

	//
	for(int i = pos; i < N; i++)
	{
		if(s+a[i] <= S) 
			if(Try(a, i+1, s+a[i])) return true;
	}
	return false;
}

int main(){
	//

	//
	int test;
	cin >> test;
	while(test--)
	{
        
		cin >> N >> S;
		int arr[N];
		for(int i=0;i<N;i++)
        {
			cin >> arr[i];
		}

		cout << ((Try(arr,0,0))?"YES": "NO" )<< endl;
		
	}

}