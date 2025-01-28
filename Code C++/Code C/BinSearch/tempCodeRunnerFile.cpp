#include <iostream>
#include <stdio.h>
#include <queue>
#include <string>
#include <vector>
#include <set>
#include <stack>
using namespace std;

#include <algorithm>

int a[100001];
int b[100001];
int BinSearch(int a[], int n, int x){
	int l = 0, r = n-1;
	while (l < r){
		int mid = (l+r)/2;
		if (a[mid] < x){
			l = mid+1;
		}
		else{
			r = mid;
		}
	}
	if (a[l] == x){
		return l;
	}
	return -1;
}

void printArr(int b[], int l, int r)
{
    for(int i = l; i <= r; i++)
    {
        cout << b[i] << " ";
    }
}

bool solve(int a[], int b[], int N, int s)
{
    int i = 1;
    b[0] = a[0];
    while (b[i-1] < s && i <= N)
    {
        b[i] = b[i - 1] + a[i];
        i++;
    }
    if(b[i] == s) 
    {
        printArr(b,0,i);
        return true;
    }
    if(b[i] > s)
    {
        int l = BinSearch(b,i+1,b[i]-s);
        if(l!= -1) 
        {
            printArr(a,n,l,i);
            return true;
        }
    }
    else return -1;

}

int main()
{
    int n, s;
	cin >> n;
	for (int i = 0; i < n; i++){
		cin >> a[i];
	}
	cin >> s;
	bool k = solve(a, b, n, s);
	if (!k){
		cout << -1;
	}
	return 0;
}
/*
    string output = String.substr(0, String.length()/2)

    for(int x: $array )

    set<vector<int>> st;

    sort(arr.begin(),arr.end()); // thay đổi arr gốc

    reverse(String.begin(),String.end()); // thay đổi string gốc
    String.erase(input.length()-1,1); // thay đổi string gốc

    template <class val>
    void swapVal(val &a , val &b)
*/