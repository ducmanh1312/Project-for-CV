#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @return

void calc(vector<int> &arr)
{
	vector<int>arr2(arr.size()-1, 0);
	cout << "[";
	for(int i = 0; i < arr.size()-1; i++)
	{
		arr2[i] = arr[i] + arr[i+1];
		cout << arr2[i];
		if(i!= arr.size()-2) cout << " ";
	}
	cout << "]" << endl;
	if(arr2.size() > 1) calc(arr2);
}

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

		cout << "[";
		for (int i = 0; i < N; i++)
		{
			cout << arr[i];
			if(i!= N-1) cout << " ";
		}
		cout << "]" << endl;
		calc(arr);

	}
}