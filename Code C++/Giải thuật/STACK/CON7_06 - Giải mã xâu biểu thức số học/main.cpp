#include <bits/stdc++.h>
using namespace std;

/// @brief 
/// @return

string check(string s)
{
	stack<char> st;
	for (int i = 0; i < s.size(); i++)
	{
		if(s[i] == ')')
		{
			bool ok = true;
			char c = st.top(); st.pop();
			while(c != '(')
			{
				if(c == '+' || c == '-' || c == '*' || c == '/')
				{
                    ok = false;
                }
				c = st.top(); st.pop();
			}

			if(ok) return "Yes";
		}
		else st.push(s[i]);
	}
	return "No";

}


int main()
{
	//

	//
	int test;
	cin >> test;
	cin.ignore();

	while (test--)
	{
		string s;
		getline(cin, s);
		cout << check(s) << endl;
	}
}