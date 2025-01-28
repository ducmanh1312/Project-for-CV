#include <bits/stdc++.h>
using namespace std;

int main()
{
    int k;
    cin >> k;
    while(k--)
    {
        long N;
        long long num, time = 0;
        cin >> N;
        priority_queue <long long, vector<long long>, greater<long long>> minHeap;


        for(long i = 0; i < N; i++)
        {
            
            cin >> num;
            minHeap.push(num);
        }

        while(minHeap.size() > 1)
        {
            long long a = minHeap.top();     minHeap.pop();
            long long b = minHeap.top() + a; minHeap.pop();
            minHeap.push(b);
            time += b;
        }
        cout << time << endl;
    }
}





