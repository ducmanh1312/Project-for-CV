#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @bug
/// @return

int main()
{

    long n,m;
    cin >> n >> m;
    map<long,long> mp;
    
    long key;
    for(long pos = 1; pos <= n; pos++)
    {
    	cin >> key;
    	if(mp[key] == 0) mp[key] = pos;
	}
	
	
	for(long i = 0; i < m; i++)
	{
		cin >> key;
		cout << mp[key] << " ";
	}
	cout << endl;
        
        
}