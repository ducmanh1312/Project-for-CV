#include <iostream>
#include <stdio.h>
#include <queue>
#include <string>
#include <vector>
#include <set>
#include <stack>
using namespace std;

#include <algorithm>



int main()
{
    int n, k;
    cin >> n;
    vector<int> arr, a, b;
    for(int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        arr.push_back(k);
        if(k > 0) a.push_back(k);
        if(k < 0) b.push_back(k);
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end()); reverse(b.begin(), b.end());

    int a1 = 0, b1 = 0;
    for(int i = 0; i < n; i++)
    {
        if(arr[i] > 0)
        {
            arr[i] = a[a1];
            a1++;
        }
        if(arr[i] < 0)
        {
            arr[i] = b[b1];
            b1++;
        }
        cout << arr[i] <<" " ;
    }
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