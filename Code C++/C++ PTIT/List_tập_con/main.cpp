#include <bits/stdc++.h>
using namespace std;

/// @brief gộp các ptu trùng lặp lại
/// @bug

/// @return số các tập con có thể tạo thành từ mảng a

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long n, b[40000];
        vector<long long> a;
        cin >> n;
        for (long long i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            a.push_back(x);
        }
        sort(a.begin(), a.end());

// Tính số tập con
    memset(b,0,sizeof(b));
    long long j = 0;
    b[0] = 1;
    for(long long i = 1; i < n; i++) // đếm các ptu trùng lặp
    {
        if(a[i] != a[i-1]) j++;
        b[j]++;
    }

    long long count = 1;
    for(long long i = 0; i <= j; i++)
    {
        count *=(b[i]+1);
    }

// In ra ptu con dài nhất
        cout << count - 1 << " [";
        for (long long i = 0; i < n; i++)
        {
            cout << a[i];
            if (i < n - 1)
                cout << ", ";
        }
        cout << "]";
        if (t != 0)
            cout << endl;
    }
}