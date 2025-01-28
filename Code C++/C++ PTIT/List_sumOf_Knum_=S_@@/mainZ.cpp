#include <bits/stdc++.h>
using namespace std;


int a[30], check[30];
int n, K, S;
int save = 0, c = 0, start = 0;
void tryit(int k)
{
    for (int j = 1 + start; j <= n - K + k; j++)
    {
        check[k] = a[j];
        start = j;
        if (k == K)
        {
            for (int l = 1; l <= K; l++)
            {
                c += check[l];
            }
            if (c == S)
            {
                save++;
            }
            c = 0;
        }
        else
            tryit(k + 1);
    }
}


int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        cin >> n >> K >> S;
        save = 0;
        c = 0;
        start = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }
        tryit(1);
        cout << save << endl;
    }
}