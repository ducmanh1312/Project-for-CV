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

int N, K;

int CountWays(int start, int k, int sum) // k số cần thêm, j là stt
{
    //
    if (sum == N && k == K)
        return 1;
    if (start > prime.size())
        return 0;
    if (sum >= N)
        return 0;
    if (k == K)
        return 0;

    int res = 0;
    for (int i = start; i <= prime.size(); i++)
    {
        if (N >= sum + prime[i]) // ĐK giúp chạy nhanh hơn
            res += CountWays(i + 1, k + 1, sum + prime[i]);
    }
    return res;
}

int main()
{
    sieve();

    int test;
    cin >> test;

    while (test--)
    {
        cin >> N >> K;

        cout << CountWays(0, 0, 0) << endl;
    }
}