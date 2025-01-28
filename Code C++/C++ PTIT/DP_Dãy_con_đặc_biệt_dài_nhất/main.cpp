#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @bug
/// @return

#define int long long
const int maxn = 1e7 + 7;
const int mod = 1e9 + 7;

int longest(vector<int>& arr) {
    int n = arr.size();          // Số lượng phần tử trong vector arr
    vector<int> dp(n, 1);         // Mảng dp để lưu độ dài dãy con dài nhất kết thúc tại vị trí i
    int maxlen = 1;               // Biến lưu trữ độ dài dãy con dài nhất

   vector<int> last(10,-1);
// Lặp qua từng chữ số của arr[i] lưu vào digits
    for (int i = 0; i < n; ++i) { 

        set<int> digits;
        int num = arr[i];
        while(num)
        {
            digits.insert(num%10);
            num /= 10;
        }
    // Duyệt qua từng chữ số trong tập hợp digits
        for(int digit: digits)
        {
            if(last[digit] != -1)
            {
                dp[i] = max(dp[i], dp[last[digit]] + 1);
                
            }
            last[digit] = i;
        }

    // Cập nhật độ dài dãy con dài nhất
        maxlen = max(maxlen, dp[i]);
    }
    return maxlen;  // Trả về độ dài dãy con dài nhất
}


int32_t main()
{

    int test;
    cin >> test;
    while (test--)
    {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> arr[i];
        }
        cout << longest(arr) << endl;
    }
}