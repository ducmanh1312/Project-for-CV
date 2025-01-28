#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @param n
/// @return

int n, K;
int a[12];

bool check[12] = {0};

void countList()
{
    long long c[K + 1];
    memset(c, 0, sizeof(c));
    c[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = min(K, i); j > 0; j--)
        {
            c[j] += c[j - 1];
        }
    }
    cout << c[K] << endl;
}

void List(int i) // Không cần sử dụng hàm check
{
    for (int j = a[i - 1] + 1; j <= n; j++)
    {
        // if (check[j] == 0)
        // {
        //     check[j] = 1;
        a[i] = j;

        if (i < K)
        {
            List(i + 1);
        }

        if (i == K)
        {
            cout << "[";
            for (int h = 1; h <= K; h++)
            {
                cout << a[h] << ((h < K) ? " " : "]\n");
            }
        }
        //     check[j] = 0;
        // }
    }
}

int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        cin >> n >> K;
        a[0] = 0;
        countList();
        List(1); // Thêm số vào vị trí i
    }
}
