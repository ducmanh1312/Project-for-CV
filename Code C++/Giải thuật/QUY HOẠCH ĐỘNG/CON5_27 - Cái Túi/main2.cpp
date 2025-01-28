#include <bits/stdc++.h>
using namespace std;

// Quy hoạch động dp[đồ vật][trọng lượng còn lại]

int knapsack(vector<int>& a, vector<int>& c, int n, int W) 
{
    // w trọng lượng túi còn trống, i đồ vật thứ i
    vector<vector<int>> dp(n+1, vector<int>(W+1, 0)); // mảng chứa trọng lượng hiện tại

    for(int i = 0; i <= n; i++) // Lặp qua từng đồ vật
    {
        for(int w = 0; w <= W; w++) // Lặp qua trọng lượng túi còn trống
        {
            if( i == 0 || w == 0) dp[i][w] = 0; // vị trí khởi đầu bằng 0
            else if(a[i-1] > w) dp[i][w] = dp[i-1][w]; // vật thứ i-1 bị quá trọng lượng => ko lấy
            else dp[i][w] = max( dp[i-1][w], dp[i-1][w-a[i-1]] + c[i-1] ); // so sánh ko lấy vật và lấy vật-> lấy trọng lượng lớn hơn
        }
    }
    return dp[n][W];
}



int main()
{
    int test;
    cin >> test;
    while(test--)
    {
        int n, W; // số vật - W trọng lượng túi
        cin >> n >> W;
        vector<int> a(n); // Mảng trọng lượng của các đồ vật
        vector<int> c(n); // Mảng giá trị của các đồ vật

        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        for (int i = 0; i < n; i++) {
            cin >> c[i];
        }

        int result = knapsack(a,c,n,W);

        cout << result << endl;
    }
}





