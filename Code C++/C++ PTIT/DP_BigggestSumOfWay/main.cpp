#include <bits/stdc++.h>
using namespace std;

/// @brief  DFS
/// @param Tại sao cần -1e9

/// @return Trả về đường đi có tổng lớn nhất trong ma trận (chọn đi từ trên xuống dưới)
int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        int m, n;
        cin >> n >> m;
        int a[n + 2][m + 2];

        for (int i = 0; i <= n; i++)
            a[i][0] = a[i][m + 1] = 0; // Tạo giá trị cho hàng trên cùng i = 0 và dưới cùng i = m+1

        for (int j = 0; j <= m; j++)
            a[0][j] = a[n + 1][j] = 0; 

        for (int i = 1; i <= n; i++) // Nhập i là chiều dọc, j là chiều ngang
        {
            for (int j = 1; j <= m; j++)
                cin >> a[i][j];
        }

        for (int i = 1; i <= n; i++) 
        {
            for (int j = 1; j <= m; j++)
                a[i][j] = a[i][j] + max(a[i - 1][j], max(a[i - 1][j - 1], a[i - 1][j + 1]));
        }

        int maxpath = 0;
        for (int j = 1; j <= m; j++)
            maxpath = max(maxpath, a[n][j]);
        cout << maxpath << endl;
    }
    return 0;
}
