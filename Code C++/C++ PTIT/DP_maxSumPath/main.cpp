#include <bits/stdc++.h>
using namespace std;

/// @brief 
/// @param n 
/// @return 
    long long n;
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
	vector<int> A;

// 1 2 3 -1 4 5 5 
void Try()
{
	for(long long i = 1; i <= n;i++) // duong di lon nhat den i
	{
		A[i] = A[i] + max(0, A[i-1]);
	}
	
	int maxPath = -1e9;
	for(int i = 1; i <= n; i++)
	{
		maxPath = max(maxPath, A[i]);
	}
	cout << maxPath << endl;
}



int main()
{
    int test;
    cin >> test;
    while(test--)
    {

        cin >> n;
        A.clear();
        A.push_back(0);
        for(long long i = 0; i < n; i++)
        {
			int num;
			cin >>num;
        	A.push_back(num);
		}
		Try();
    }
}
