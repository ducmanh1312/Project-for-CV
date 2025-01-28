#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return xâu con dài nhất
/// @note 

int dp(int a[], int N)
{
	int lis[N]; // dộ dài xâu con dài nhất kết thúc tại i
	lis[0] = 1;

	for(int i=1; i<N; i++)
	{
		lis[i] = 1;
		for(int j=0; j<i; j++)
		
		{
			if(a[j] < a[i] && lis[j]+1 > lis[i])
			{
				lis[i] = lis[j] + 1; // cập nhật lại dộ dài xâu con dài nhất kết thúc tại i
			}
		}

	}
	return *max_element(lis, lis+N);
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