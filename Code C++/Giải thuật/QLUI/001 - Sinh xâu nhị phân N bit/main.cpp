#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @return

int N;

int x[100]; // array contain n-bit string

void cout_arr(int x[]) // print current array
{
    for (int i = 1; i <= N; i++)
        cout << x[i] << " ";
    cout << endl;
}

void Try(int i)
{
    for (int j = 0; j <= 1; j++)
    {
        x[i] = j;
        if (i == N) // Đk dừng
            cout_arr(x);
        else
            Try(i + 1);
    }
}

void Try2(int i)
{
    if (i == N+1) // Đk dừng
    {
        cout_arr(x);
        return;
    }

    for (int j = 0; j <= 1; j++)
    {
        x[i] = j;
        Try2(i + 1);
    }
}

int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        cin >> N;
        Try(1);
    }
}