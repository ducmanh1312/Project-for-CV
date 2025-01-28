#include<bits/stdc++.h>
using namespace std;

/// @brief lặp từ dưới lên; lưu operand vào stack; nếu gặp operator thì lấy 2 operand ra ghép => 1 operand mới => stack
/// @return 

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

string preToPost(string pre_exp) 
{
 
    stack<string> s; // chứa toán hạng 
	int length = pre_exp.length();

	for(int i = length - 1; i >=0; i--) 
	{
		if(isOperator(pre_exp[i]))
		{
			string op1 = s.top();
			s.pop();
			string op2 = s.top();
			s.pop();

			s.push(op1 + op2 + pre_exp[i]);
		}
		else 
		{
			s.push(string(1,pre_exp[i]));
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
		string pre_exp;
        cin >> pre_exp;
        cout << preToPost(pre_exp) << endl;
	}

}