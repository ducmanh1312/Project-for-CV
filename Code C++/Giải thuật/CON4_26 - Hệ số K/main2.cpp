// C++ implementation to find the
// sum of two integers of base B

#include <bits/stdc++.h>
using namespace std;

#define ll long long

// Function to find the sum of
// two integers of base B
string sumBaseB(string a, string b, int base)
{
	int len_a, len_b;

	len_a = a.size();
	len_b = b.size();

	string sum, s;
	s = "";
	sum = "";

	int diff;
	diff = abs(len_a - len_b);

	// Padding 0 in front of the
	// number to make both numbers equal
	for (int i = 1; i <= diff; i++)
		s += "0";

	// Condition to check if the strings
	// have lengths mis-match
	if (len_a < len_b)
		a = s + a;
	else
		b = s + b;

	int curr, carry = 0;

	// Loop to find the find the sum
	// of two integers of base B
	for (int i = max(len_a, len_b) - 1; i > -1; i--)
	{

		// Current Place value for
		// the resultant sum
		curr = carry + (a[i] - '0') + (b[i] - '0');

		// Update carry
		carry = curr / base;

		// Find current digit
		curr = curr % base;

		// Update sum result
		sum = (char)(curr + '0') + sum;
	}
	if (carry > 0)
		sum = (char)(carry + '0') + sum;
	return sum;
}

// Driver Code
int main()
{
	int test;
	cin >> test;
	while (test--)
	{
		ll k, tmp = 1, num1 = 0, num2 = 0;
		string a, b, res = "";
		cin >> k >> a >> b;

		string sum = sumBaseB(a, b, k);
		cout << sum << endl;
	}
}
