#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @bug  ** Đk lọc **
/// @return  số cách biểu diễn N thành tổng của K số Fibonacci, không tính hoán vị.

int fibo[100] = {0};

void fibonaci()
{
    fibo[0] = 1;
    fibo[1] = 2;
    for (int i = 2; i <= 50; i++)
        fibo[i] = fibo[i - 1] + fibo[i - 2];
}

int Try(long N, int k, int stt)
{
    // Đk dừng
    if (k == 0 && N == 0)  return 1;
    if (k == 0) return 0;
    if (N == 0) return 0;    

    //
    int sum = 0;
    for (int i = stt; i >= 0 and fibo[i] * k >= N; i--) // Đk lọc
	{
        if (N >= fibo[i]) sum += Try(N - fibo[i], k-1, i);
    }
    return sum;
}
 
int main(){
 int t;
 cin >> t;
 while (t--){
     fibonaci();
     int n, K = 2;
     cin >> n >> K;
     cout << Try(n, K, 42) << endl;
  }
    return 0;
}