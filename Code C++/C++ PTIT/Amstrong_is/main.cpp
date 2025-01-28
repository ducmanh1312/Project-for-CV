#include <bits/stdc++.h>
using namespace std;

// Hàm đếm số chữ số
int countDigits(long long n)
{
    int count = 0;
    while (n > 0) {
        n /= 10;
        count++;
    }
    return count;
}
// Hàm kiểm tra có phải số Amstrong
long long isAmstrong(long long n)
{
    int count = countDigits(n);
    long long temp = 0;
	while(n > 0)
    {
        temp += pow(n%10, count);
    }
    return temp;
}

int main()
{
    int test;
    cin >> test;
    while(test--)
    {
        long long n;
        cin >> n;
        cout << (isAmstrong(n) == n) << endl;
    }
}
