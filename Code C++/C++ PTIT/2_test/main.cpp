#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/// @brief
/// @bug 
/// @return m ch? s? d?u tiên trong k?t qu? tính n^k

void findFirstM(ll N, ll K, ll M) // tính M ch? s? d?u c?a
{
	float y = K * log10(N);
	y = y - (ll)y;
	double temp = pow(10.0, y + M - 1);
	cout << fixed << setprecision(0) << (temp) << endl;
	
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
} // M ch? s?
