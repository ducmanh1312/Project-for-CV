#include <bits/stdc++.h>
using namespace std;

// 9/10
int arr[100005];
int N,K,S;

int Try(int start, int k, int s) // 0 - 0 - 0
{
    // Đk dừng
    if(s == S && k == K) return 1;
    if(start == N) return 0;
    if(k == K) return 0;
    if(s >= S) return 0;
    
    // Duyệt
    int result = 0;
    for(int i = start; i < N; i++)
    {
        if(S >= s + arr[i]) result += Try(i+1, k+1, s + arr[i]);
    }
    return result;
}

int main()
{
    int test;
    cin >> test;
    while(test--)
    {
        cin >> N >> K >> S;

        memset(arr,0,sizeof(arr));
        
        for(int i = 0; i < N; i++)
        {
            cin >> arr[i];
        }

        cout << Try(0,0,0) << endl;

    }
}





