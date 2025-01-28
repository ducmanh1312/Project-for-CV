#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @return

int main()
{
	//

	//
	int test;
	cin >> test;
	while (test--)
	{
		int N;
		cin >> N;
		vector<int> arr(N);
		for (int i = 0; i < N; i++)
		{
			cin >> arr[i];
		}
		next_permutation(arr.begin(), arr.end());

		for (auto i : arr)
		{
			cout << i << " ";
		}
		cout << endl;
	}
}