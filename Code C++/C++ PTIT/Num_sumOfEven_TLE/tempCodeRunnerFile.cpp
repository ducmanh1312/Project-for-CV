#include <bits/stdc++.h>

using namespace std;

long sumOfEven(long l, long r)
{
    long sum = 0;
    if(l%2 == 0) l++;
    if(r%2 == 0) r--;
    for(long i = l; i <= r; i += 2)
    {
        sum += i;
    }
    return sum;
}

int main()
{
    int test;
    cin >> test;
    while(test--)
    {
        long l, r;
        cin >> l >> r;

        cout << sumOfEven(l,r) << endl;
    }
}
