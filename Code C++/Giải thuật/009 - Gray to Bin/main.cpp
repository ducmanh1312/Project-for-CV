#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return gray -> bin

string Try(string gray)
{
	string bin = "";
	bin += gray[0];
	for(int i = 1; i < gray.size(); i++)
	{
		if(gray[i] != bin[i-1]) bin += "1";
		else bin += "0";
	}
	return bin;
}

int main(){
	int test;
	cin >> test;
	while(test--)
	{
        string gray;
		cin >> gray;

		cout << Try(gray) << endl;
		
	}

}