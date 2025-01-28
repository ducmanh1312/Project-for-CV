#include <iostream>
#include <stdio.h>

#include <algorithm>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <set>

using namespace std;

void quickSort(int a[], int l, int r)
{
}

int main()
{
    int n, a[10001], k = 1, max = 0, temp;
    vector<int> vt;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        vt.push_back();
    }
    sort(vt.begin(), vt.end());

    for (int i = 0; i < n; i++)
    {
        if (vt.begin() + i + k > max)
        {
            max = vt.begin() + i + k;
        }
        k++;
    }
    cout << max;
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