#include <bits/stdc++.h>
using namespace std;

/// @brief Sử dụng tính chất của modulo
/// @param 
/// @return 

typedef long long ll;
const int Mod = 1e9 + 7;


ll du(string a, ll m) // Hàm chuyển xâu a => số nguyên modulo m
{
    ll r = 0;
    for (char x : a)
    {
        r = (r * 10) + (x - '0');
        r = r % m;
    }
    return r;
}

ll pow(ll a, ll b) // Hàm tính a^b modulo m
{
    ll res = 1;
    while (b)
    {
        if (b % 2 == 1) // nhân khi bit của b = 1
        {
            res *= a;
            res %= Mod; // lấy modulo res để tránh tràn số
        }
        b >>= 1;

        a *= a; // bình phương a
        a %= Mod; // Lấy modulo a
        
    }
    return res;
}





int main()
{
    int tess;
    cin >> tess;
    while (tess--)
    {
        string a;
        ll b;
        cin >> a >> b;  // Nhập a(string) và b(long long)
        ll r = du(a, Mod);  // Chuyển a sang dạng số đã chia modulo
        cout << pow(r, b) << endl;  // Tính mũ kèm modulo
    }
    return 0;
}
