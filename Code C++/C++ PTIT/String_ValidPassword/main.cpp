#include <bits/stdc++.h>
using namespace std;

ifstream input("password.in");
ofstream output("res.out");

bool valid_string(string str)
{
    bool hasUpperCase = false;
    bool hasLowerCase = false;
    bool hasDigit = false;
    bool hasSpecialChar = false;
    char prevchar = '\0';
    
    if(str.length() < 8) return false;

    for(char c: str)
    {
        if(isupper(c)) hasUpperCase = true;
        if(islower(c)) hasLowerCase = true;
        if(isdigit(c)) hasDigit = true;
        if(ispunct(c)) hasSpecialChar = true;

        if(c == prevchar) return false;
        prevchar = c;
    }
    
    return hasUpperCase && hasLowerCase && hasDigit && hasSpecialChar;
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





