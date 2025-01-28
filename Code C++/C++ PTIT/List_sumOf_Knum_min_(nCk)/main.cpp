#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @bug
/// @return

int ToHop(int n, int k) // nCk
{
    if(k > n - k) k = n - k;
    int C[k+1];
    memset(C,0,sizeof(C));

    C[0] = 1;
    for(int i = 0; i < n; i++)
    {
        for(int j = k; j > 0; j--)
        {
            C[k] += C[k-1];
        }
    }
    return C[k];
}

int Daycon(int arr[], int n, int k)
{
    sort(arr, arr + n);
    int num = arr[k - 1];
    int count = 0; 
    for (int i = k - 1; i >= 0; i--) // đếm số num cuối giống nhau trong dãy con
    {
        if (arr[i] == num)
            count++;
    }
    int dem = count;
    for (int i = k; i < n; i++) // số số bằng num cuối
    {
        if (arr[i] == num)
            dem++;
    }
    
    return ToHop(dem, count);
}

int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        int n, k;
        cin >> n >> k;
        int arr[n];
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        cout << Daycon(arr, n, k) << endl;
    }
    return 0;
}