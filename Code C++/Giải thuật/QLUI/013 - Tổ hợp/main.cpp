#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 

int N,K;

void Try(int k, int start, string res)
{
	if(k == K)
	{
		cout << res << " ";
		return;
	}
	if(start == N) return;

	//
	for(int i = start+1; i <= N; i++)
	{
		Try(k+1, i, res + to_string(i)); 
	}
}

int main(){
	int test;
	cin >> test;
	while(test--)
	{

		cin >> N >> K;

		Try(0,0,"");
		cout << endl;
		
	}

}