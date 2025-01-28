#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 

int N;
bool check[10];

void Try(int pos, long res)
{
	for(int i = 1; i <= N; i++)
	{
		if(check[i])
		{
			// Borrow
			check[i] = false;
			res = res*10 + i;


			if(pos == N)
			{
				cout << res << " ";
			}
			else
				Try(pos+1, res);

			//Pay
			res /= 10;
			check[i] = true;
		}
	}
}

void Try2(int pos, long res)
{
	//
	if(pos == N)
	{
		cout << res << " ";
		return;
	}

	//
	for(int i = 1; i <= N; i++)
	{
		if(check[i])
		{
			check[i] = false;
			Try2(pos+1, res*10 + i );
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