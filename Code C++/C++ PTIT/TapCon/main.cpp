#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @bug

/// @return Trả lại kết quả tổng tất cả các tập con có thể tạo thành từ mảng a

void sxtang(long long a[], long long n)
{
    long long i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (a[i] > a[j])
                swap(a[i], a[j]);
        }
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long n, a[40000], b[40000]; 
        memset(b,0,sizeof(b));
        cin >> n;
        
        for (long long i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        sxtang(a, n);

// Tính số tập con
    long long j = 0;
    b[0] = 1;
    for(long long i = 1; i < n; i++)
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