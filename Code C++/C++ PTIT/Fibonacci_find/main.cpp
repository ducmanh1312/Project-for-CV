#include <bits/stdc++.h>
using namespace std;

/// @brief 
/// @bug
/// @return số Fibonacci tại vị trí cho trước tại vị trí n (bắt đầu từ số 0)

const int mod = 10e9 + 7;
struct matrix
{
    long long f[2][2];
};

matrix operator*(matrix A, matrix B)
{
    matrix res;
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            res.f[i][j] = 0;
            for(int k = 0; k < 2; k++)
            {
                res.f[i][j] = (res.f[i][j] + (A.f[i][k] * B.f[k][j]) % mod) % mod;
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

    
    }
}