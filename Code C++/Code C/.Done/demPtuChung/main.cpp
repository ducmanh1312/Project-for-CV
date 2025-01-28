#include <iostream>
#include <stdio.h>
#include <queue>
#include <string>
#include <vector>
#include <set>
#include <stack>
using namespace std;

#include <algorithm>

int commonCharacterCount(string s1, string s2)
{
    vector<int> a(256);
    vector<int> b(256);
    for(int i = 0; i < s1.size(); i++)
    {
        a[s1[i]]++;
    }
    for(int i = 0; i < s2.size(); i++)
    {
        b[s2[i]]++;
    }
    int d = 0, num = 'a',den = 'z';
    for(int i = num; i <= den; i++)
    {
        d += min(a[i],b[i]);
    }
    
}

int main()
{
    
}

/*
    string output = String.substr(0, String.length()/2)

    for(int x: $array )

    set<vector<int>> st;

    sort(arr.begin(),arr.end()); // thay đổi arr gốc

    reverse(String.begin(),String.end()); // thay đổi string gốc
    String.erase(input.length()-1,1); // thay đổi string gốc

    template <class val>
    void swapVal(val &a , val &b)
*/