#include <iostream>
#include <stdio.h>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

int maximizeSum(std::vector<int> arr)
{
    int n = arr.size();
    int sum = 0;
    for(int i = 0; i < n; i++)
    {
        sum += arr[i] + 
    }
}

int main()
{
    
}

int numberOfToys(std::vector<int> arr, int k)
{
    sort(arr.begin(),arr.end());
    int i = 0, temp = 0;
    while(k - arr[i]>0)
    {
        temp++;
        k -= arr[i++];
    }
    return temp;
}

int mettingRoom(std::vector<int> s, std::vector<int> f)
{
    int n = s.size();
    vector<pair<int, int>> meeting(n);
    for(int i = 0; i < n; i++)
    {
        meeting[i] = {f[i], s[i]};
    }
    sort(meeting.begin(),meeting.end());
    int count = 1;
    int end = meeting[0].first;
    for(int i = 1; i < n; i++)
    {
        if(meeting[i].second >= end)
        {
            count++;
            end = meeting[i].first;
        }
    }
    return count;
}


/*

*/