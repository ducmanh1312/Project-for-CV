#include <bits/stdc++.h>
using namespace std;

/// @brief 
/// @param n 
/// @return 

/*
	sort(result.begin(), result.end(), <bolean function>); 
	
*/

long long findString(string s)
{
	string child, parent;
    stringstream input(s);
    vector<string> out;
	while(getline(input, child, '\"'))
    {
		out.push_back(child);
    }
	out[1].erase(0, 1);
	out[3].erase(0, 1);
	
	
	return out[3].find(out[1]);
}

int main()
{
    int test;
    cin >> test;
    while(test--)
    {
        string input;
        getline(cin, input, '\n');
        cout << findString(input) <<endl;
    }
}
