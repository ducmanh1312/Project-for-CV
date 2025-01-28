#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 

int N,K;

int Try(int start, int sum)
{
	//
	if(sum == N) return 1;
	if(sum > N) return 0;

	// 
	int res = 0;
	for(int i = start; i <= N; i++)
	{
		res += Try(i, sum + i ); 
	}

	return res;

}

int main(){
	int test;
	cin >> test;
	while(test--)
	{

		cin >> N;
	
		cout << Try(1,0) << endl;

		
	}

}