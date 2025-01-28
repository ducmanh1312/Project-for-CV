#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @return tổng lớn nhất dãy con Bi-tonic của dãy số arr[]
/// @note

int calc(int arr[], int n)
{
    int MIS[n], MDS[n];
    for (int i = 0; i < n; i++)
    {
        MIS[i] = arr[i];
        MDS[i] = arr[i];
    }

    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            if (arr[j] < arr[i] && MIS[j] + arr[i] > MIS[i])
                MIS[i] = MIS[j] + arr[i];

    for (int i = n-2; i >= 0; i--)
        for (int j = n-1; j > i; j--)
            if (arr[j] < arr[i] && MDS[j] + arr[i] > MDS[i])
                MDS[i] = MDS[j] + arr[i];

    int res = 0;
    for (int i = 0; i < n; i++)
        res = max(res, MIS[i] + MDS[i] - arr[i]);

    return res;
}

int main()
{
    //

    //
    int test;
    cin >> test;
    while (test--)
    {
        int N;
        cin >> N;
        int arr[N];
        for (int i = 0; i < N; i++)
        {
            cin >> arr[i];
        }
        cout << calc(arr, N) << endl;
    }
}