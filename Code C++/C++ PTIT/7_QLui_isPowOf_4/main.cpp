#include <bits/stdc++.h>
using namespace std;

/// @brief 
/// @bug
/// @return Kiểm tra xem số đầu vào có phải là số mũ của số 4 hay không

bool Try(long long n)
{
     if(n == pow(4, (long long)(log(n)/log(4))) && n != 0)
        return true;
    return false;
}

int main()
{

    int test;
    cin >> test;

    while (test--)
    {
        long long n;
        cin >> n;

        cout << Try(n) << endl;
    
    }
}