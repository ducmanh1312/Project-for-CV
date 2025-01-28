#include <iostream>
// IN:
// OUT:
#include <cmath>
#define FOR(i, start, end) for (int i = start; i <= end; i++)
#define ll long long
#define ull unsigned long long
using namespace std;


ll max4(ll x1, ll x2, ll x3, ll x4)
{
    return max(x1,max(x2,max(x3,x4)));
}
ll min4(ll x1, ll x2, ll x3, ll x4)
{
    return min(x1,min(x2,min(x3,x4)));
}

ll distance(ll x1, ll x2, ll x3, ll x4)
{
    return abs(x1-x2)+abs(x3-x4)-(max4(x1,x2,x3,x4)-min4(x1,x2,x3,x4));
}

int main()
{
    ll x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

    ll m = distance(x1, x2, x3, x4);
    cout << distance(x1, x2, x3, x4)*distance(y1,y2,y3,y4);
}

/*

*/