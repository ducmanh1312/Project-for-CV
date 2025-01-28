#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 

void Try(string s, int pos)
{
	if(pos == s.size()) 
	{
		cout << s << endl;
		return;
	}

	if(s[pos] == '?')
	{
		s[pos] = '0';
		Try(s, pos+1);
		
		s[pos] = '1';
		Try(s, pos+1);
	}
	else
	{
		Try(s, pos+1);
	}
}



int main(){
	int test;
	cin >> test;
	while(test--)
	{
		string s;
		cin >> s;

		Try(s,0);
		
	}

}