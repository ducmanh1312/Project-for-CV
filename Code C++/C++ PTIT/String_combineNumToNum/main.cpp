#include <bits/stdc++.h>
using namespace std;

/// @brief 
/// @bug
/// @return số lớn nhất bằng cách ghép các phần tử của dãy lại với nhau

bool xapxep(string a, string b)
{
	if(a.compare(b) > 0) 
        return true; // a > b
    return false;
}

int main()
{

    int test;
    cin >> test;

    while (test--)
    {
        int n;
        cin >> n;
        vector<string> s;
        for(int i = 0; i < n; i++)
        {
            string temp;
            cin >> temp;
            s.push_back(temp);
        }

        sort(s.begin(), s.end(), xapxep);       /////////////

        for(int i = 0; i < n; i++)
        {
            cout << s[i];
        }
        cout << endl;
    }
}
















