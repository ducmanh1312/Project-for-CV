#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/// @brief 
/// @param 
/// @return trả về số số 0 ở cuối n!
long calc0(long long n)
{
	long res = 0;
	while(n >= 5)
	{
		res += (n/5);
		n /= 5;
	}
	
	return res;
}

long long find(long long n)
{
	long long start = 0;
	long long end = 5*n;
	

	while(start < end)
	{
		long long mid = (start + end)/2;
		
		if(calc0(mid) < n)
		{
			start = mid + 1;
			
		}
		else
		{
			end = mid;
		}
	}
	return end;
}

int main()
{
	int test = 1;
	cin >> test;
	while(test--)
	{
		long long n;
		cin >> n;
		cout << find(n) << endl;
	}
}