#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @bug
/// @return

vector<int> prime;

// Sieve array of prime
bool isprime[1000];

void sieve()
{
    memset(isprime, true, sizeof(isprime));

    // Sieve of Eratosthenes.
    for (int i = 2; i * i <= 1000; i++)
    {
        if (isprime[i])
        {
            for (int j = i * i; j <= 1000; j += i)
            {
                isprime[j] = false;
            }
        }
    }

    // Push all the primes into
    // prime vector
    for (int i = 2; i <= 1000; i++)
    {
        if (isprime[i])
        {
            prime.push_back(i);
        }
    }
}

// DP array
int dp[200][20][1000];
// k số chữ số ngto hiện tại, i: stt số ngto đang xét, sum tổng hiện tại

int N = 0, K = 0;

int CountWays(int i, int k, int sum) // 0 0 0 
{
    //
    if(sum == N && k == K ) return 1;

    if(i > prime.size() ) return 0;
    if(sum >= N) return 0;
    if(k == K) return 0;

    //
    if(dp[i][k][sum]) return dp[i][k][sum];

    return dp[i][k][sum] = CountWays(i+1, k+1, sum + prime[i]) + CountWays(i+1, k, sum);
}

int main()
{
    sieve();

    int test;
    cin >> test;

    while (test--)
    {
        cin >> N >> K;

        memset(dp, 0, sizeof(dp));
        cout << CountWays(0, 0, 0) << endl;
    }
}