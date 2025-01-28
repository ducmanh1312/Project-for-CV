#include <bits/stdc++.h>
using namespace std;

/// @brief  DFS
/// @param Tại sao cần -1e9

/// @return Trả về đường đi có tổng lớn nhất trong ma trận (chọn đi từ trái sang phải)
int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        int m, n;
        cin >> m >> n;
        int a[m + 2][n + 2];

        for (int i = 0; i <= m; i++)
            a[i][0] = a[i][n + 1] = 0; // Tạo giá trị cho hàng trên cùng i = 0 và dưới cùng i = m+1

        for (int j = 0; j <= n; j++)
            a[0][j] = a[n+1][j] = 0; // Tạo giá trị cho hàng trên cùng i = 0 và dưới cùng i = m+1


        for (int i = 1; i <= m; i++) // Nhập i là chiều dọc, j là chiều ngang
        {
            for (int j = 1; j <= n; j++)
                cin >> a[i][j];
        }

        // int maxpath = -1e9;
        // for (int j = 1; j <= n; j++)
        //     maxpath = max(maxpath, a[0][j]);
        // cout << maxpath << endl;

        for (int i = 1; i <= m; i++) // Tìm đường có tổng lớn nhất từ cột [1] đến a[i][j]
        {
            for (int j = 1; j <= n; j++)
                a[i][j] = a[i][j] + max(a[i - 1][j], max(a[i - 1][j - 1], a[i - 1][j + 1]));
        }


        int maxpath = -1e9;
        for (int j = 1; j <= n; j++)
            maxpath = max(maxpath, a[n][j]);
        cout << maxpath << endl;
    }
    return 0;
}
