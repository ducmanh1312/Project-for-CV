#include <iostream>
#include <vector>
#include <cmath>
using namespace std;



const long MAX_N = 1000000; // Giới hạn n lớn nhất
bool is_prime[MAX_N + 1];   // Mảng đánh dấu số nguyên tố

// Hàm sàng để tạo danh sách các số nguyên tố
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

// Hàm kiểm tra xem một số có phải là số nguyên tố hoàn toàn hay không
bool isFullPrime(long num)
{
    if (!is_prime[num])
    {
        return false;
    }
    while (num > 0)
    {
        int digit = num % 10;
        if (!is_prime[digit])
        {
            return false;
        }
        num /= 10;
    }
    return true;
}

int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        long n;
        cin >> n;
        sieve(); // Tạo danh sách các số nguyên tố
        int count = 0;
        for (long i = 2; i <= n; ++i)
        {
            if (isFullPrime(i))
            {
                count++;
            }
        }
        cout << count << endl;
    }
}
