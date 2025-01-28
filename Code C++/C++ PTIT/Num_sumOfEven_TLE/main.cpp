#include <bits/stdc++.h>

using namespace std;

long sumOfEven(long l, long r)
{
    long sum = 0;
    if(l%2 == 0) l++;
    if(r%2 == 0) r--;
    sum = ((r-l)/2+1)*((l+r)/2);
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
