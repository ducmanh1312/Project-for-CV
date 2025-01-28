#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

// Hàm nhân ma trận
vector<vector<long long>> matrixMultiply(vector<vector<long long>>& A, vector<vector<long long>>& B) 
{
    int N = A.size();
    vector<vector<long long>> result(N,vector<long long>(N,0));
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            for(int k = 0; k < N; k++)
            {
                result[j][i] = (result[j][i] + A[j][k] * B[k][i]) % MOD;
            }
        }
    }

    return result;
}

//    A(x,z)*B(z,y) = A(x,y)

int main()
{
    int test;
    cin >> test;
    while(test--)
    {
        int result;
        cout << result << endl;
    }
}





