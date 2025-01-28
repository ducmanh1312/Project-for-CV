#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 
/// @note 

void rearrange(vector<int> &A, int N)
{
    vector<int> sorted = A;
	sort(sorted.begin(), sorted.end());

	map<int, int> pos;

	for(int i = 0; i < N; i++)
	{
		pos[A[i]] = i;
	}

	int ans = 0;
	for(int i = 0; i < N; i++)
	{
		if(A[i] != sorted[i])
		{
			ans++;
			swap(A[i], A[pos[sorted[i]]]);
			swap(pos[A[i]], pos[A[pos[sorted[i]]]]);
		}
	}
	cout << ans << endl;

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
		vector<int> A(N, 0);

		for(int i = 0; i < N; i++)
			cin >> A[i];

		rearrange(A,N);
		
	}

}