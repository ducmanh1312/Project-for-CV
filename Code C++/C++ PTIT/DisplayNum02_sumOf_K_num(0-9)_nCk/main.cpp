#include <bits/stdc++.h>
using namespace std;

/// @brief tính chỉnh hợp C(N + K - 1, K - 1) 
/// @bug

/// @return Hãy đếm số cách biểu diễn N thành tổng của K số tự nhiên 0-9

long long calc(int N, int K)
{
    if (K > N - K)
        K = N - K;

    long long arr[N + 2];
    memset(arr, 0, sizeof(arr));
    arr[0] = 1;

    for (int i = 1; i <= N; i++)
    {
        for (int j = K; j > 0; j--)
        {
            arr[j] += arr[j - 1];
        }
    }
    return arr[K];
}

int main()
{
    int test = 1;
    cin >> test;

    while (test--)
    {
        int n, k;
        cin >> n >> k;
        cout << calc(n + k - 1, k - 1) << endl;
    }
}