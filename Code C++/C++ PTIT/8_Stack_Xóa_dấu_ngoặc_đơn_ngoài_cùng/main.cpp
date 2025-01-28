#include <bits/stdc++.h>
using namespace std;

/// @brief 
/// @bug
/// @return 

void check(string s)
{
	stack<char> st;
	string res;
	for(char c: s)
	{
		if(st.empty()) st.push(c);
		else
		{
			
			if( c == '(' ) 
			{
				st.push(c);
				res += c;
			}
			else 
			{
				st.pop();
				if(!st.empty()) res += c;
			}
		}
		if(st.empty())
		{
			cout << res;
			res = "";
		}
	}
	cout << endl;
}

int main()
{

    int test;
    cin >> test;

    while (test--)
    {
		string s; 
		cin >> s;
		check(s);
    }
}