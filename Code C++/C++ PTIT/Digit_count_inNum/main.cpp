#include <bits/stdc++.h>

using namespace std;

long arr[10];

void countDigits(long num)
{
    
    while(num > 0)
    {
        arr[num%10]++;
        num /= 10;
    }
}
// Đếm digit xuất hiện của các số trong khoảng a, b
long countDigitsInRange(long a, long b)
{
        if (a == 0 || b == 0)
        {
            arr[0]++;
        }
    while(a <= b)
    {
        countDigits(a);
        a++;
    }
}


int main()
{
    int test;
    cin >> test;
    while(test--)
    {
        long a, b;
        cin >> a >> b;
        memset(arr,0,sizeof(arr));
        if(a > b) swap(a,b);
        countDigitsInRange(a,b);
        for(int i = 0; i < 10; i++) cout << arr[i] << " ";
        cout << endl;
        
    }
}
