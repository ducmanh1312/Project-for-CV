#include <bits/stdc++.h>
using namespace std;


bool isSafe(vector<vector<int>>& board, int row, int col, int N)
{
    // kiểm tra cột
    for(int i = 0; i < row; i++)
    {
        if(board[i][col]) return false;
    }

    // kiểm tra chéo phải
    for(int i = row, j = col; i >= 0 && j < N; i--, j++)
    {
        if(board[i][j]) return false;
    }

    // kiểm tra chéo trái
    for(int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if(board[i][j]) return false;
    }
    return true;
}

int solveNQueens(vector<vector<int>>& board, int row, int N) 
{
    if( row == N ) return 1;
    int count = 0;

    for(int col = 0; col < N; col++) // duyệt qua từng hàng
    {
        if(isSafe(board,row,col,N)) 
        {
            board[row][col] = 1;
            count += solveNQueens(board, row+1, N); // sng cột tiếp theo duyệt tiếp
            board[row][col] = 0; // trả
        }
    }
    return count;
}

int  N_Queens(int n)
{
    vector<vector<int>> board(n,vector<int>(n,0));
    return solveNQueens(board, 0, n);
}

int main()
{
    int test;
    cin >> test;
    while(test--)
    {
        int n;
        cin >> n;
        
        int result = N_Queens(n);
        cout << result << endl;
    }
}





