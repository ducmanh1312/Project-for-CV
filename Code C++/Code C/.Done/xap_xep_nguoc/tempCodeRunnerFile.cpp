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
    int n,temp;
    vector<int> st;
    while(n--)
    {
        cin >> temp;
        st.push_back(temp);
        for(int i = st.size(); i >= 0; i--)
        {