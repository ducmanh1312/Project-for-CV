#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 

#define MAX_COUNT 10000
char c[2] ={'9', '0'};

vector<string> vec;

void Try()
{
	queue<string> q;
	q.push("9");

	for(int i = 0; i < MAX_COUNT; i++)
	{
		string s1 = q.front();
		q.pop();

		vec.push_back(s1);

		q.push(s1 + "0");
		q.push(s1 + "9");
	}
}

string findmin(int n)
{
	for(int i = 0; i < vec.size(); i++)
	{
		if(stoi(vec[i]) % n == 0) return vec[i];
	}

	//
}

int main(){
	//
	Try();	

	int test;
	cin >> test;
	while(test--)
	{
        int n;
		cin >> n;

		cout <<findmin(n) << endl;
		
	}

}