#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 
/// @note 

int calc(vector<pair<int, int>> &vt)
{
	sort(vt.begin(), vt.end());
	int ans[vt.size()];
	for (int i = 0; i < vt.size(); i++)
	{
		ans[i] = 1;
		for (int j = 0; j < i; j++)
		{
			if (vt[j].second < vt[i].first && ans[j]+1 > ans[i])
                ans[i] = ans[j]+1;
		}
	}
	return *max_element(ans, ans+vt.size());
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
		vector<pair<int, int>> vt;
		for(int i = 0; i < N; i++)
		{
			int a,b;
			cin >> a >> b;
			vt.push_back(pair<int, int>(a,b));
		}
		cout << calc(vt) << endl;
		
	}

}