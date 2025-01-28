#include <iostream>
#include <fstream>
#include <string>

using namespace std;




int main()
{
    int i;
    cin >> i;
    while(i--)
    {
        int cost, change, money;
        cin >> cost >> change >> money;

        int n = money / cost;
        int box = n;
        while(box > change)
        {
            box -= change;
            box++;
            n++;
        }
        cout << n << endl;     
    }
}