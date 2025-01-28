#include <bits/stdc++.h>
using namespace std;

char arr[2] = {'0', '1'};

int N, K;
void Try(int n, int k, string s)
{
	if (n == N 
	&& k == K
	)
	{
		cout << s << endl;
		return;
	}
	if (n == N)
		return;

	for (int j = 0; j <= 1; j++)
	{
		if (arr[j] == '1')
			Try(n+1, k+1, s + arr[j]);
		else 
			Try(n+1, k, s + arr[j]);

	}
}

int main()
{
	int test;
	cin >> test;
	while (test--)
	{
		cin >> N >> K;
		Try(0, 0, "");
	}
}