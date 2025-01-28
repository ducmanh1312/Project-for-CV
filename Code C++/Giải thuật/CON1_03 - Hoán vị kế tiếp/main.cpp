#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @return

int N;

void cout_arr(int x[]) // print current array
{
    for (int i = 0; i < N; i++)
        cout << x[i] << " ";
    cout << endl;
}

void Try(int arr[])
{
    int pos = 0;
    int min = N-1;
    for(int i = N-2; i >= 0; i--)
    {

        if(arr[i] < arr[i+1])
        {
            pos = i;
            for(int j = i+1; j < N; j++)
            {
                if(arr[j] > arr[i] && arr[min] > arr[j]) min = j;
            }
            break;
        }
    }

    if(pos == 0)
    {
        reverse(arr, arr + N);
        return;
    }else
    {
        swap(arr[pos], arr[min]);
        reverse(arr + pos + 1, arr + N);
    }

}

int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        // cin >> N;
        N = 6;
        int arr[N];
        for (int i = 0; i < N; i++)
        {
            cin >> arr[i];
        }

        Try(arr);
        cout_arr(arr);
    }
}