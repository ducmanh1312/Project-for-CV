#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 

int N;
bool check[10];

void Try(int pos, long res)
{
	//
	if(pos == N)
	{
		cout << res << " ";
		return;
	}

	//
	for(int i = N; i > 0; i--)
	{
		if(check[i])
		{
			check[i] = false;
			Try(pos+1, res*10 + i );
			check[i] = true;
		}
	}
}

int main(){
	int test;
	cin >> test;
	while(test--)
	{
		cin >> N;
		memset(check,true,sizeof(check));

		Try(0,0);
		cout << endl;
		
	}

}