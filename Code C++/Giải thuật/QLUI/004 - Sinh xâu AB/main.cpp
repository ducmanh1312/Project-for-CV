#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @return

char arr[2] = {'A', 'B'};
int N;

void Try(int pos, string s)
{
	for (int i = 0; i <= 1; i++)
	{
		if (pos == N-1)
		{
			cout << s + arr[i] << " ";
		}
		else 
			Try(pos + 1, s + arr[i]);
	}
}

void Try2(int pos, string s)
{
	//
	if (pos == N)
	{
		cout << s << " ";
		return;
	}

	//
	for (int i = 0; i <= 1; i++)
	{
		Try2(pos + 1, s + arr[i]);
	}
}

int main()
{
	int test = 1;
	cin >> test;
	while (test--)
	{

		cin >> N;
		string s = "";

		Try(0, "");
		cout << endl;
	}
}