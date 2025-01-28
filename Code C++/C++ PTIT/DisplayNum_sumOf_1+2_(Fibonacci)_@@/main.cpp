#include <bits/stdc++.h>
using namespace std;

/// @brief số cách biểu diễn N là số fibonacci thứ (N+1) + Lũy thừa a trận
/// @bug
/// @return số cách biểu diễn số thành tổng của các số 1 và 2

const int mod = 1e9 + 7;
struct Matrix
{
    long long f[2][2];
};

// Hàm nhân ma trận A*B
Matrix operator*(Matrix A, Matrix B)
{
    Matrix C;
    int i, j, k;
    for (i = 0; i <= 1; i++)
    {
        for (j = 0; j <= 1; j++)
        {
            C.f[i][j] = 0;
            for (k = 0; k <= 1; k++)
                C.f[i][j] = (C.f[i][j] + (A.f[i][k] * B.f[k][j]) % mod) % mod;
        }
    }
    return C;
}

// tính lũy thừa ma trận A^n
Matrix powerMod(Matrix A, int n)
{
    // if (n == 0) return 1;
    if (n == 1)
        return A;

    //
    Matrix X = powerMod(A, n / 2); 
    if (n % 2 == 0)
        return X * X;
    return A * X * X;
}


/* Tạo ma trận A
    1 1
    1 0
Tính A^n =
fibo(n+1) fibo(n)
fibo(n)   fibo(n-1)

*/
long long Fibo(int n)
{
    Matrix A;
    A.f[0][0] = 1;
    A.f[0][1] = 1;
    A.f[1][0] = 1;
    A.f[1][1] = 0;
    Matrix KQ = powerMod(A, n);
    return KQ.f[0][1];
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        cout << Fibo(n) << endl;
    }
    return 0;
}