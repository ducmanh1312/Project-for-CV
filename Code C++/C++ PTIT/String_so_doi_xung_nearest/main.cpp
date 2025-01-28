#include <bits/stdc++.h>
using namespace std;

/// @brief
/// @param n
/// @return

typedef long long ll;

bool Ktdoixung(string n) {
	for (int i = 0; i < n.size() / 2; i++)
		if (n[i] != n[n.size() - 1 - i])
			return    false;
	return true;
}

string NUMBER_to_String(ll num) {
	if (num == 0)
		return "0";
	string Snum = "";
	while (num > 0) {
		Snum += (num % 10 - '0');
		num /= 10;
	}
	return Snum;
}

void Sodoixunggannhat(ll num) {
	ll numT = num - 1;
	while(!Ktdoixung(NUMBER_to_String(numT))) {
		numT--;
	}

	ll numS = num + 1;
	while(!Ktdoixung(NUMBER_to_String(numS))) {
		numS++;
	}

	if(abs(numS - num) > abs(num - numT)) cout << numT << endl;
	else if(abs(numS - num) < abs(num - numT)) cout << numS << endl;
	else cout << numT << " " << numS << endl ;

}
int main() {
	int test;
	cin >> test;
	while (test--) {
		ll num;
		cin >> num;
		if (Ktdoixung(NUMBER_to_String(num))) {
			cout << num;
		} else if (num < 9) {
			cout << num;
		} else Sodoixunggannhat(num);
	}
	return 0;
}
