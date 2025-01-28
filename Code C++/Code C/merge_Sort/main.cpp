#include <iostream>
#include <stdio.h>
#include <queue>
#include <string>
#include <vector>
#include <set>
#include <stack>
using namespace std;

#include <algorithm>



vector<int> Merge_Sort(vector<int> A)
{

    int n = (int)A.size(), k = (n - 1) / 2;

    vector<int> B, C;
    for (int i = 0; i <= k; i++)
        B.push_back(A[i]);
    for (int i = k + 1; i < n; i++)
        C.push_back(A[i]);

    if ((int)B.size() > 1)
        B = Merge_Sort(B);
    if ((int)C.size() > 1)
        C = Merge_Sort(C);

    A.clear();
    A.resize(B.size() + C.size());
    merge(B.begin(), B.end(), C.begin(), C.end(), A.begin());

    return A;
}



int main()
{
    int n, temp;
    cin >> n;
    vector<int> A;

    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        A.push_back(temp);
    }
    A = Merge_Sort(A);

    int k;
    cin >> k;
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if(i == 0 || A[i]-A[i-1] > k) count++;
    }
    cout << count;
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