#include <bits/stdc++.h>
using namespace std;

/// @brief 
/// @bug
/// @return Tính số lượng học sinh không được ăn

void Try(string stu1, string cake1)
{
    stringstream ss(stu1), sc(cake1);
    string temp;
    int tmp;
    deque<int>stu, cake;

    while(getline(ss, temp, ','))
    {
        stringstream num(temp);
        num >> tmp;
        stu.push_back(tmp);
    }

    
    while(getline(sc, temp, ','))
    {
        stringstream num(temp);
        num >> tmp;
        cake.push_back(tmp);

    }

    int i = 0;
    while(i < stu.size())
    {
        if(stu.front() == cake.front())
        {
            stu.pop_front();
            cake.pop_front();
            i = 0;
        }else
        {
            stu.push_back(stu.front());
            stu.pop_front();
            i++;
        }
    }

    cout << i << endl;

}

int main()
{

    int test;
    cin >> test;

    while (test--)
    {
        string student, cake;
        cin >> student >> cake;

        Try(student, cake);
    
    }
}