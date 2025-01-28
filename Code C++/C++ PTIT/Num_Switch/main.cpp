#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// thay num chứa 3 bằng 5
int max(int a, int b)
{
    string a1 = to_string(a);
    string b1 = to_string(b);
    for (char &c : a1)
    {
        if (c == '3')
            c = '5';
    }
    for (char &c : b1)
    {
        if (c == '3')
            c = '5';
    }
    return stoi(a1) + stoi(b1);
}

// thay num chứa 5 bằng 3
int min(int a, int b)
{
    string a1 = to_string(a);
    string b1 = to_string(b);
    for (char &c : a1)
    {
        if (c == '5')
            c = '3';
    }
    for (char &c : b1)
    {
        if (c == '5')
            c = '3';
    }
    return stoi(a1) + stoi(b1);
}

int main()
{
    int i;
    cin >> i;
    while (i--)
    {
        int a, b;
        cin >> a;
        cin >> b;
        cout << min(a, b) << " " << max(a, b) << endl;
    }
}