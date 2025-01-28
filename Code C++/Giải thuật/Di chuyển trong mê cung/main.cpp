//Di chuyen trong me cung 
#include<bits/stdc++.h>
using namespace std;

#define MAX 10
int ii[4] = {+1, -1, 0, 0};
int jj[4] = {0, 0, +1, -1};
int A[MAX][MAX];
bool visited[MAX][MAX];
int N, Vonghiek = false;
int X[MAX*MAX];
int sopt = 0;
void Hienthi(int X[], int sopt){
	for(int i=0; i<sopt; i++)
	if(X[i]==0)      cout <<"D";
	else if(X[i]==1) cout <<"U";
	else if(X[i]==2) cout <<"R";
	else             cout <<"L";
	cout << " ";
	Vognghiem = true;
}
void Timduongdi(int x, int y){
	for(int k=0; k<4; k++)
	   if(A[x+ii[k]][y+jj[k]] && !visited[x+ii[k]][y+jj[k]]){
	   	   X[sopt++] = k;
	   	   visited[x+ii[k]][y+jj[k]] = true;
	   	   if(x+ii[k] == N && y+jj[k] == N){
	   	   	     Hienthi(X, sopt);
			}else
			Timduongdi(x+ii[k], y+jj[k]);
			visited[x+ii[k]][y+jj[k]] = false;
			sopt--;
	   }
}

int main(){
	int t;
	cin >> t;
	while(t--){
		//Nhap du lieu vao
		cin >> N;
		memset(A, 0, sizeof(A));
		memset(visited, 0, sizeof(visited));
		for(int i = 1; i<=N; i++)
		   for(int j = 1; j<=N; j++) cin >> A[i][j]; 
		    //Xu ly
		    Vognghie = false;
		    visited[1][1] = true;
		    Timduongdi(1, 1);
		    if(!Vognghiem) cout << "-1"<< endl;
		    else cout << endl;
	}
	return 0;
}