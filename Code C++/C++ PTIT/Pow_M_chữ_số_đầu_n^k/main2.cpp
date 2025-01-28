#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/// @brief dugnf string
/// @bug
/// @return m chữ số đầu tiên trong kết quả tính n^k

string multiply(string &num1, string &num2){
    int m = num1.size();
    int n = num2.size();

    string res(m + n, '0'); 
    for(int i = m-1; i >= 0; i--)
    {
        int carry = 0;
        for(int j = n-1; j >= 0; j--)
        {
            int tmp = (num1[i] - '0') * (num2[j] - '0') + (res[i + j + 1] - '0') + carry;
            carry = tmp / 10;
            res[i + j + 1] = (tmp % 10) + '0';
        }
        res[i] += carry;
    }

    int pos = -1;
    for(int i = 0; i < res.size(); i++)
    {
        if(res[i] != '0')
        {
            pos = i;
            break;
        }
    }

    if(pos != -1)
    {
       
        return res.substr(pos);
    }else
    {
        return "0";
    }
}

string power(string &a, int n){
    string result = "1";
    for (int i = 0; i < n; i++){
        result = multiply(result, a);
    }
    return result;
}

int main(){
    int t;
    cin >> t;
	while(t--){
		string a;
		cin >> a;
		int n, k;
		cin >> n >> k;
		string res = power(a, n);
        
		for(int i = 0; i < k; i++){
			cout << res[i];
		}
		cout << endl;
	}
    return 0;
}
