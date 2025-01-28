#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/// @brief dùng logarit
/// @bug 
/// @return m chữ số đầu tiên trong kết quả tính n^k

void findFirstM(ll N, ll K, ll M) // tính M chữ số đầu của
{
    float y = (float)K * log10(N);           // y = số chữ số của N
    y = y - (ll)y;                             // 0.xyz
    double temp = pow(10.0, y);                // chuyển y về dạng thập phân double
    ll firstM = temp * (1LL) * pow(10, M - 1); // 10^0.xyz * 10^(M-1)
    // Print the result
    cout << firstM << endl;
}

// 2^30 = 107374...

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long int N;
        int mu, chuso;
        cin >> N >> mu >> chuso;
        if (N == 0)
            cout << "0";
        else
            findFirstM(N, mu, chuso);
    }
    return 0;
} // M chữ số