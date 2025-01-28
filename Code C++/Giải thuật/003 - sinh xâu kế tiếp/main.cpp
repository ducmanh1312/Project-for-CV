#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 

string Try(string s)
{
	int i;
	for(int i = s.size()-1; i >= 0; i--)
	{
		if(s[i] == '0')
		{
			s[i] = '1';
			break;
		}
		else
		{
			s[i] = '0';
		}
	}

	if (i < 0)
        s = "1" + s;
    return s;
}

int main(){

	int test;
	cin >> test;
	while(test--)
	{
		string s;
		cin >> s;

		cout << Try(s) << endl;
		
	}
}