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

int calc(int op1, int op2, char x)
{
    switch (x) {
    case '+':
        return op2 + op1;
    case '-':
        return op2 - op1;
    case '/':
        return op2 / op1;
    case '*':
        return op2 * op1;
    }
    return 0;
}
 
// Count postfix 
int postToIn(string post_exp)
{
    stack<int> s;
 
    int length = post_exp.size();
 
    for (int i = 0; i < length; i++) {
 
        if (isOperator(post_exp[i])) {
 
            int op1 = s.top();
            s.pop();
            int op2 = s.top();
            s.pop();
 
            s.push(calc(op1, op2, post_exp[i]));
        }
 
        // if symbol is an operand
        else {
            s.push(post_exp[i] - '0');
        }
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
        cout << postToIn(s) << endl;
		
	}

}