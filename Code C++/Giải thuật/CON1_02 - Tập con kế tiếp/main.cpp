#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @return

int N, K;

void cout_arr(int x[]) // print current array
{
    reverse(x, x+K);
    for (int i = 0; i < K; i++)
        cout << x[i] << " ";
    cout << endl;
}

void Try(int arr[])
{
    int temp = K-2;
    for(int i = 0; i <= K-1; i++)
    {
        if(arr[i] < N - i)
        {
            arr[i]++;
            temp = i-1;
            break;
        }
        if(i == K-1) arr[i] = 1;
    }

    for(int i = temp; i >= 0; i--)
    {
        arr[i] = arr[i+1]+1;
    }

    return;

}

int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        cin >> N >> K;
        int arr[K + 1];
        for (int i = K-1; i >= 0; i--)
        {
            cin >> arr[i];
        }

        Try(arr);
        cout_arr(arr);
    }
}