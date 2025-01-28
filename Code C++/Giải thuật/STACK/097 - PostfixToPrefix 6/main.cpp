#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return Convert postfix to Prefix expression

// function to check if character is operator or not
bool isOperator(char x)
{
    switch (x) {
    case '+':
    case '-':
    case '/':
    case '*':
        return true;
    }
    return false;
}
 
string postToPre(string post_exp)
{
    stack<string> s; // operand stack
    int length = post_exp.size();
 
    for (int i = 0; i < length; i++) {
 
        // check if symbol is operator
        if (isOperator(post_exp[i])) {
 
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();
 
            s.push(post_exp[i] + op2 + op1);
        }
 
        // if symbol is an operand
        else {
            s.push(string(1, post_exp[i]));
        }
    }
 
    string ans = "";
    while (!s.empty()) {
        ans += s.top();
        s.pop();
    }
    
    return s.top();
}

int main(){
	//

	//
	int test;
	cin >> test;
	while(test--)
	{
        string s;
        cin >> s;
        cout << postToPre(s) << endl;
		
	}

}