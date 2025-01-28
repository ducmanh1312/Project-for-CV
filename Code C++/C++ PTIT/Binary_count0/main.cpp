#include <bits/stdc++.h>
using namespace std;

// Đếm số 0 trong số binary
int countNumbers(long long N,long long K) {
    int count = 0;

    for (int i = 0; i <= N; ++i) {
        long long num = i;
        int zeroCount = 0;

        while (num > 0) {
            if (num % 2 == 0) {
                zeroCount++;
            }
            num /= 2;
        }

        if (zeroCount == K) {
            count++;
        }
    }

    return count;
}

int main()
{
    int test;
    cin >> test;
    while(test--)
    {
        long long n, k;
        cin >> n >> k;
        cout << countNumbers(n,k) << endl;
    }
}





