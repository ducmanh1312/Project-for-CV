#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @bug

/// @return  đếm số lượng các ô cờ khác nhau mà quân mã có thể đi qua sau k bước di chuyển.

int XX[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int YY[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// Hàm đệ quy lặp qua bàn cờ
void Try(vector<vector<bool>> &chess, int x, int y, int k, int n)
{
    if(k == 0) return;
    for(int i = 0; i < 8; i++)
    {
        int tx = x + XX[i];
        int ty = y + YY[i];
        if(tx >= 0 && tx < n && ty >= 0 && ty < n)
        {
            chess[tx][ty] = true;
            Try(chess, tx, ty, k-1, n);
        }
    }
}

// Hàm đếm số vị trí mã đã đi qua
int dem(int n, int k, int x, int y)
{
    vector<vector<bool>> chess(n, vector<bool>(n, false));
    chess[x][y] = true;
    Try(chess, x, y, k, n);
    int dem = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(chess[i][j] == true) dem++;
        }
    }
    return dem;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k, x, y;
        cin >> n >> k >> x >> y;
        cout << dem(n, k, x - 1, y - 1) << endl;
    }
}