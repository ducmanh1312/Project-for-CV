#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @return

int arr[10000];

vector<int> dp(100, 0);
vector<int> end_pos(100, 0);
vector<int> trace(100, 0);

int bin_search(int max, int val)
{
	int res = 0;

	int start = 1;
	int end = max;
	while (start <= end)
	{
		int mid = (start + end) >> 1;
		if (arr[end_pos[mid]] < val)
		{
			res = mid;
			start = mid + 1;
		}
		    
		else
			end = mid-1;

		return res;
	}
}

int Try(int n)
{
	int max = 1;
	end_pos[max] = 1;

	for(int i = 0; i < n; i++){
		int length = bin_search(max, arr[i]);

		if(length + 1 > max){
			max = length + 1;
            end_pos[max] = i;
		}
		else if(arr[max] > arr[i])
			arr[max] = arr[i];

		dp[i] = length + 1;
		trace[i] = end_pos[max];
	}

	cout << max << endl;
}

int main()
{
	//

	//
	int test = 1;
	// cin >> test;
	while (test--)
	{
		int N;
		cin >> N;

		for (int i = 0; i < N; i++)
			cin >> arr[i];

		Try(N);
	}
}