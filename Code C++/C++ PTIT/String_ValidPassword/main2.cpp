#include <bits/stdc++.h>
using namespace std;

ifstream input("password.in");
ofstream output("res.out");

bool valid_string(string password)
{
    regex pattern("(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#$%^&*()\\-+]).{8,}");

    if (!regex_match(password, pattern))
    {
        return false;
    }

    for (long long i = 1; i < password.length(); ++i)
    {
        if (password[i] == password[i - 1])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    string str;
    while(getline(input, str))
    {
        if(valid_string(str))
        {
            output << "VALID" << endl;
        }else
        {
            output << "INVALID" << endl;
        }
    }

}





