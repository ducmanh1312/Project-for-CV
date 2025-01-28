#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @bug
/// @return số lần chèn abc vào xâu để tạo ra xâu kết quả

void calc(string s, int k) 
{
	// return fast
	if(k > s.size()) 
	{
		cout << 0 << endl;
		return;
	}
	
	// calc
	deque<char> st;
	for(char c: s)
	{	
		while(!st.empty() && c < st.back() && k > 0 )
		{
			st.pop_back();
			k--;
		}
		st.push_back(c);
	}
	
	
	while(k > 0 && !st.empty()) // nếu k thừa
	{
		st.pop_back();
		k--;
	}
	
	
	// print
	while(!st.empty() && st.front() == '0')
	{
		st.pop_front();
	}
	
	if(st.empty())
	{
		cout << 0 << endl;
	}
	else
	{
		while(!st.empty())
		{
			cout << st.front();
			st.pop_front();
		}
		cout << endl;	
	}
}

int main()
{

	int test;
	cin >> test;
	while(test--)
	{
			string s;
			int k;
			cin >> s >> k;
			
			calc(s,k);
	}
}