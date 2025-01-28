#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int test;
    cin >> test;
    while (test--)
    {
        int i = 0, n, count = 0, result[10];
        double sum = 1;
        cin >> n;

        if (n == 1)
        {
            count++;
            result[1] = 0;
        }
        while (sum < n + 1)
        {
            i++;
            sum += log(i) / log(10);
            if (sum >= n)
            {
                count++;
                result[count] = i;
            }
        }

        if (count - 1)
        {
            cout << count - 1 << " ";
            for (i = 1; i < count; i++)
                cout << result[i] << " ";

            cout << endl;
        }
        else
            cout << "NO" << endl;
    }
}