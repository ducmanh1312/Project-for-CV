#include <bits/stdc++.h>
using namespace std;

/// @brief  DFS
/// @param

/// @return Trả về đường đi chi phí nhỏ nhất

int n, m,
    ans = INT_MAX,  // tổng chi phí nhỏ nhất
    cmin = INT_MAX; // Giá trị nhỏ nhất của các chi phí c

int c[500][500], // Chi phí giữa các đỉnh
    check[50],   // Kiểm tra đỉnh đó đá đi qua chưa
    luu[50],     // Tổng chi phí hiện tại
    truoc[500];  // Lưu các đỉnh trước đó

void Try(int k) // Tìm đường đi từ đỉnh 1 đến đỉnh k
{
    for (int i = 2; i <= n; ++i)
    {
        if (check[i] == 0 && c[truoc[k - 1]][i] != 0) // Kiểm tra đã đi qua i chưa và có đường đi ko
        {
            check[i] = 1;
            
            luu[k] = luu[k - 1] + c[truoc[k - 1]][i]; // Cập nhật chi phí mới
            truoc[k] = i;

            if (k == (n - 1))
            {
                if (c[i][1])
                    ans = min(ans, luu[k] + c[i][1]); // So sánh đường đi đến đích vừa tính với đường đi cũ
            }
            else if (luu[k] + cmin * (n - k) < ans) // So sánh đường đã đi với ước lượng đường đi nhỏ nhất
                Try(k + 1);

            check[i] = 0;
        }
    }
}

int main()
{
    int k, j, c0;
    truoc[0] = 1;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {
        cin >> k >> j >> c0;
        c[k][j] = c0;
        cmin = min(cmin, c0);
    }
    Try(1);
    cout << ans;
    return 0;
}