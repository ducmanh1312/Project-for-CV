#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 
/// @note 

void rearrange(int A[], int N)
{
    int temp[N];
    int low = 0, high = N - 1;
    int flag = true;
	int i = 0;

	while(i < N) 
	{
		if(i%2 == 0)temp[i++] = A[high--];
		else temp[i++] = A[low++];

	}

	for(int i = 0; i < N; i++)
	    cout << temp[i] << " ";

	cout << endl;

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
		int A[N];

		for(int i = 0; i < N; i++)
			cin >> A[i];

		sort(A,A+N);

		rearrange(A,N);
		
	}

}