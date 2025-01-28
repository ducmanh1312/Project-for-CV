#include <iostream>
#include <stdio.h>
#include <queue>
#include <string>
#include <vector>
#include <set>
#include <stack>
using namespace std;

#include <algorithm>

int interpolationSearch(int a[], int n, int x)
{
    int l = 0, r = n-1;
    while(a[r]!= a[l] && x >= a[l] && x<= a[r])
    {
        mid = l + (r-l)*(x-a[l])/(a[r]-a[l]);
        if(a[mid] < x)
        {
            l = mid + 1;
        }else if(a[mid] > x)
        {
            r = mid;
        }else
        {
            
        }
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