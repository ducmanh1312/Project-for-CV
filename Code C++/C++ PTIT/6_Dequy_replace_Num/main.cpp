#include <bits/stdc++.h>

using namespace std;

#define ll  unsigned long long


/// @brief 
/// @param 
/// @return Tìm số bước nhỏ nhất để biến đổi n
ll count (ll n)
{
    if(n < 2) return n;
    ll result = 0;
    ll i = sqrt(n);
    result = 1 + min(count(n/3) + n%3, min(count(n/2) + n%2, count(i) + n-i*i));
    return result;
}

int main()
{
    int test;
    cin >> test;
    while(test--)
    {
        ll n;
        cin >> n;
        cout << count(n) << endl;
    }
}
