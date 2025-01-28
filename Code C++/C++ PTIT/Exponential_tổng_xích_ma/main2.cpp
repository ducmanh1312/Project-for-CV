#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

// Hàm nhân ma trận
vector<vector<long long>> matrixMultiply(vector<vector<long long>>& A, vector<vector<long long>>& B) {
    int N = A.size();
    vector<vector<long long>> result(N, vector<long long>(N, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                result[i][j] = (result[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }

    return result;
}

// Hàm tính ma trận mũ
vector<vector<long long>> matrixPower(vector<vector<long long>>& A, int k) {
    int N = A.size();
    vector<vector<long long>> result(N, vector<long long>(N, 0));

    // Khởi tạo ma trận kết quả bằng ma trận đơn vị
    for (int i = 0; i < N; i++) {
        result[i][i] = 1;
    }

    while (k > 0) {
        if (k % 2 == 1) {
            result = matrixMultiply(result, A);
        }
        A = matrixMultiply(A, A);
        k /= 2;
    }

    return result;
}

int main() {
    int N, k;
    cin >> N >> k;

    vector<vector<long long>> A(N, vector<long long>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> A[i][j];
        }
    }

    vector<vector<long long>> result = matrixPower(A, k);

    // In ra ma trận kết quả
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
