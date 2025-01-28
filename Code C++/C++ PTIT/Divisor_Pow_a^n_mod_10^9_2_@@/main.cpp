#include <bits/stdc++.h>
using namespace std;

/// @brief Sử dụng tính chất của modulo
/// @param
/// @return

//HÀM MŨ SỐ LỚN
#define int long long
const int maxn = 1e7 + 7;
const int mod = 1e9 + 7;

// Lũy thừa nhị phân x^y mod
int modpow(int x , int y, int mod){
    int res = 1 ;
    x = x % mod ;

    while(y > 0){
        if(y % 2 == 1){
            res = (res * x) % mod ;
        }
        y = y / 2 ;
        x = (x * x) % mod;
    }
    return res;
}
void implement(){
    string a , b ;
    cin >> a >> b ;
    int x = 0 , y = 0 ; // x = a mod, y  = b mod

    for(auto c: a)
    {
        x = (x*10 + (c - '0')) % mod;
    }
    for(auto c: b)
    {
        y = (y*10 + (c - '0')) % (mod - 1);
    }

    cout << modpow(x, y, mod);
}
int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while(t--){
        implement();
        cout << endl;
    }
    return 0;
}