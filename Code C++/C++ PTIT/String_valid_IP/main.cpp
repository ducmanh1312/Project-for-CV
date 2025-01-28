
#include <bits/stdc++.h>
using namespace std;

// Hàm kiểm tra token trong ip hợp lệ
bool isValidToken(string s)
{
    int temp = stoi(s);
    if (temp >= 0 && temp <= 255 && s == to_string(temp))
        return true;
    return false;
}

// Hàm kiểm tra ip hợp lệ
int is_valid(string ip)
{
    stringstream ss(ip);
    string token;
    while (getline(ss, token, '.'))
    {
        if (!isValidToken(token))
            return false;
    }
    return true;
}

// Hàm đếm số string thỏa mãn đk ip
int dem(string ip)
{
    int l = ip.length();
    int count = 0;
    string check = ip;
    for (int i = 1; i <= l-3 ; i++)
    {
        for (int j = i+1; j <= l-2 ; j++)
        {
            for (int k = j+1; k <= l-1; k++)
            {
                check = check.substr(0,k) + '.' + check.substr(k);
                check = check.substr(0,j) + '.' + check.substr(j);
                check = check.substr(0,i) + '.' + check.substr(i);
                if(is_valid(check)) count++;
                check = ip;
            }
        }
    }

    return count;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        string ip;
        cin >> ip;
        cout << dem(ip) << endl;
    }
    return 0;
}
