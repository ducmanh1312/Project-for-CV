#include <bits/stdc++.h>

using namespace std;

string findSum(string string1, string string2)
{
    string result = "";
    int n1 = string1.size();
    int n2 = string2.size();
    if (n1 > n2)
    {   
        swap(n1, n2);
        swap(string1, string2);
    }
    reverse(string1.begin(), string1.end());
    reverse(string2.begin(), string2.end());    // n1 <= n2

    int nho = 0;
    for (int i = 0; i < n2; i++)
    {
        int temp =  string2[i] - '0' + nho;
        if(i < n1) temp += string1[i] - '0';
        result.push_back(temp % 10 + '0');
        nho = temp / 10;
    }

    if (nho)
    {
        result.push_back(nho + '0');
    }
    reverse(result.begin(), result.end());

    return result;
}

int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        string str1;
        string str2;
        cin >> str1 >> str2;
        cout << findSum(str1, str2) << endl;
    }
}
