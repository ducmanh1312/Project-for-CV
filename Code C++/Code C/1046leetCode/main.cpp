#include <iostream>
#include <stdio.h>
#include <queue>
#include <string>
#include <vector>
#include <set>
#include <stack>
using namespace std;

#include <algorithm>

class Solution
{
public:
    int lastStoneWeight(vector<int> &a)
    {
        priority_queue<int>pq(a.begin(), a.end());
        
        while(pq.size() > 1)
        {
            int a = pq.top();
            pq.pop();
            int b = pq.top();
            if( a != b) pq.push(abs(a-b));
        }
        return (pq.empty()) ?0 :pq.top();
    }
};

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