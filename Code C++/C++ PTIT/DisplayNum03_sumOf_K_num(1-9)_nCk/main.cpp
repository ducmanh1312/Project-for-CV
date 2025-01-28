#include <bits/stdc++.h>
using namespace std;

/// @brief bt chia kẹo => result = (N-1)C(K-1) 
/// @bug

/// @return số cách biểu diễn N thành tổng của K số tự nhiên khác 0

long long calc(int N, int K)
{
	if(K > N) return 0;
	if(K >  N - K) K = N - K;
	
	long long arr[52];
	memset(arr, 0, sizeof(arr));
	arr[0] = 1;

	for(int i = 1; i <= N; i++) // tính bằng tam giác pascal
	{
		for(int j = K; j > 0; j--)
		{
			arr[j] += arr[j-1];
		}
	}	
	return arr[K];
}


int main() {
    int test = 1;
    cin >> test;

    while (test--)
    {
        int n, k;
        cin >> n >> k;
        cout << calc(n-1,k-1) << endl;
    }
}