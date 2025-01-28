#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return bin -> gray

string Try(string bin)
{
	string gray = "";
	gray += bin[0];
	for(int i = 1; i < bin.size(); i++)
	{
		if(bin[i] != bin[i-1]) gray += "1";
		else gray += "0";
	}
	return gray;
}

int main(){
	int test;
	cin >> test;
	while(test--)
	{
        string bin;
		cin >> bin;

		cout << Try(bin) << endl;
		
	}

}