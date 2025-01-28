#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @param 
/// @return Phân thích n thành tích của P^A

#define ll long long
void solve(ll n)
{
    map<ll, int> mp; // Lặp qua tất cả các ước số lưu vào map
    if (n % 2 == 0)
    {
        while (n % 2 == 0)
        {
            mp[2]++;
            n /= 2;
        }
    }
    for (ll i = 3; i <= sqrt(n); i += 2)
    {
        if (n % i == 0)
        {
            while (n % i == 0)
            {
                mp[i]++;
                n /= i;
            }
        }
    }
    if (n != 1)
        mp[n]++;

    cout << mp.size() << endl;
    for (map<ll, int>::iterator it = mp.begin(); it != mp.end(); it++)
        cout << (*it).first << " " << (*it).second << endl;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        solve(n);
    }
    return 0;
}