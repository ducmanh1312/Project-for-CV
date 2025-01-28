#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @return
void Try(string s)
{

	deque<string> dq;
	deque<string> level;
	string head = " ";

	stringstream ss(s);
	string node;
	while (getline(ss,node, ' '))
	{
		if (dq.empty())
		{
			dq.push_back(node);
			level.push_back(" ");
		}
		else if (node == "-1")
		{
			if (head != level.front())
			{
				head = level.front();
				cout << endl;
			}

			cout << dq.front() << " ";
			dq.pop_front();
			level.pop_front();
		}
		else
		{
			dq.push_back(node);
			level.push_back(dq.front());
		}
	}
	while (!level.empty())
	{
		if (head != level.front())
		{
			cout << endl;
			head = level.front();
		}
			
		cout << dq.front() <<  " ";

		dq.pop_front();
		level.pop_front();
	}
}



int main()
{
	//

	//
	int test;
	cin >> test;
	while (test--)
	{
		string s;
		cin.ignore(1, '\n');
		getline(cin, s);
		Try(s);


		
	}
}