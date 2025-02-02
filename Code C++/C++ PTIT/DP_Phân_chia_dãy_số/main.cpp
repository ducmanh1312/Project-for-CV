#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @bug
/// @return

#define int long long
const int maxn = 1e7 + 7;
const int mod = 1e9 + 7;
#define MAXN 41
#define MAXTOTAL 820

bool dp[MAXN][MAXTOTAL]; // kiểm tra xem có thể có một tập con của tổng là j không.

int minarr(int arr[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; ++i)
        sum += arr[i];
    memset(dp, false, sizeof(dp));

    for (int i = 0; i <= n; ++i)
        dp[i][0] = true;

    for (int i = 1; i <= n; ++i) // duyệt qua các ptu mảng arr
    {
        for (int j = 1; j <= sum / 2; ++j) // duyệt qua từng tổng từ 1 đến sum/2
        {
            dp[i][j] = dp[i - 1][j] || (j >= arr[i - 1] && dp[i - 1][j - arr[i - 1]]);
        }
    }
    
    // Tìm giá trị j max sao cho dp[n][j] là true
    for (int j = sum / 2; j >= 0; --j)
    {
        if (dp[n][j])
            return sum - 2 * j;
    }
    return sum;
}
void implement()
{
    int n;
    cin >> n;
    int arr[MAXN];
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }
    cout << minarr(arr, n);
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        implement();
        cout << endl;
    }
    return 0;
}
