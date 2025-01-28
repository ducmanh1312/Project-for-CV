#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 
/// @note 

int calc(int n)
{
	//
	if(n == 1 or n == 2 or n == 3 or n == 4 or n == 5) return n;

	//
	set<long long> s;
	s.insert(1);
	n--;

	//
	while(n--)
	{
		int x = *s.begin();
		s.insert(x*2);
		s.insert(x*3);
		s.insert(x*5);

		s.erase(s.begin());
	}
	return *s.begin();

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
		cout << calc(N) << endl;
	}

}