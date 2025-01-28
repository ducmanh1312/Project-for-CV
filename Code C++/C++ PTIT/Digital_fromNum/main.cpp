#include <bits/stdc++.h>
#include <vector>
using namespace std;

vector<int> numToDigital(long long n)
{
    vector<int> arr;
    while(n > 0)
    {
        arr.push_back(n%2);
        n /= 2;
    }
    return arr;

}

// 4 = 100
int main()
{
    int test;
    cin >> test;
    while(test--)
    {
        long long n;
        cin >> n;

        vector<int> arr = numToDigital(n);
        for(long long i = arr.size()-1; i >= 0; i-- )
        {
            cout << arr.at(i);
        }
        cout << endl;
    }
}
