#include <bits/stdc++.h>

using namespace std;

const long MAX_N = 1000000; // Giới hạn n lớn nhất
bool is_prime[MAX_N + 1];   // Mảng đánh dấu số nguyên tố

// Hàm sàng để tạo danh sách các số nguyên tố( tối đa 10^6 chữ số)
void sieve()
{
    fill(is_prime, is_prime + MAX_N + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (long i = 2; i <= sqrt(MAX_N); ++i)
    {
        if (is_prime[i])
        {
            for (long j = i * i; j <= MAX_N; j += i)
            {
                is_prime[j] = false;
            }
        }
    }
}



int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        long l, r;
        cin >> l >> r;
        sieve();
        long count = 0;
        for(long i = l; i <= r; i++)
        {
            if(is_prime[i]) count++;
        }
        cout << count << endl;
    }
}
