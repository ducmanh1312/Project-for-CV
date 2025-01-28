#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @param n
/// @return dãy hoán vị các số từ 1 đến 15 (ko lặp lại)

short int n;
short int a[17];
bool check[17] = {0};

bool Try(int i)
{
    for (int j = 1; j <= n; j++) // Lặp qua từng số trong mảng
    {
        if (check[j] == 0) // Nếu số đó chưa được thêm
        {
            a[i] = j;   // thêm số đó vào mảng a
            check[j] = 1; 
            if (i < n)
            {
                Try(i + 1); // Lặp qua các số để thêm vào vị trí tiếp theo
            }

            if (i == n) // Nếu đã thêm đủ số vào mảng a
            {
                for (int h = 1; h <= n; h++)
                {
                    cout << a[h] << (h < n ? " " : "\n");  // NOTE
                }
            }
            check[j] = 0; // xóa số đã thêm vào
        }        
    }
}

int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        cin >> n;
        Try(1);
    }
}