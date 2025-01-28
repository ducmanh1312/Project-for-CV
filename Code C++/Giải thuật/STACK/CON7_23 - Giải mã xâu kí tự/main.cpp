#include <bits/stdc++.h>
using namespace std;

/// @brief 
/// @return

void decoder(string s)
{
	stack<int> integerstack;
	stack<char> stringstack;

	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			// duyệt hết count => đẩy vào stack
			int count = 0;
			while (s[i] >= '0' && s[i] <= '9')
			{
				count = count * 10 + s[i] - '0';
				i++;
			}
			i--;

			integerstack.push(count);
		}
		else if (s[i] == '[')
		{
			stringstack.push('[');
		}
		else if (s[i] == ']')
		{
			// lấy string ra => lấy count => Nhân => đẩy lại vào stringstack
			string temp = "";
			while (!stringstack.empty() && stringstack.top() != '[')
			{
				temp = stringstack.top() + temp; //cộng đảo ngược
				stringstack.pop();
			}
			stringstack.pop();

			int count = 0;
			if (!integerstack.empty())
			{
				count = integerstack.top();
				integerstack.pop();
			}

			string result = "";
			for (int j = 0; j < count; j++)
			{
				result += temp;
			}

			for (int j = 0; j < result.size(); j++)
				stringstack.push(result[j]);
		}
		else
		{
            stringstack.push(s[i]);
        }
	}

	// return string
	string result = "";
    while (!stringstack.empty())
    {
        result = stringstack.top() + result; //cộng đảo ngược
        stringstack.pop();
    }

    cout << result << endl;
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
		cin >> s;
		decoder(s);
	}
}