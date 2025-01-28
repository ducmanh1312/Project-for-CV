#include <bits/stdc++.h>
using namespace std;

int arr[100000];
int N,K,S;
int res = 0;

int Try(int start, int k, int s)
{

    for(int i = start; i < N; i++)
    {
        s += arr[i];
        k++;
        if(k == K)
        {
            if(s == S) res++;
        }
        else Try(i+1, k, s);

        s -= arr[i];
        k--;
    }
    return res;
}

int main()
{
    int test;
    cin >> test;
    while(test--)
    {
        cin >> N >> K >> S;
        
        for(int i = 0; i < N; i++)
        {
            cin >> arr[i];
        }

        cout << Try(0,0,0) << endl;

    }
}





















