#include <bits/stdc++.h>
using namespace std;

char arr[2] = {'0','1'};

void Try( int n)
{
	for(int i = 0; i < (1 << n); i++)
	{
		int val = (i ^ (i >> 1));
		
		bitset<32> r(val);

		string s = r.to_string();
		cout << s.substr(32-n) << " ";
	}
	cout << endl;
    return;
}


int main(int argc, char** argv) {
	int test;
	cin >> test;
	while(test--)
	{
		int N;
		cin >> N;
		Try(N);
	}
}