#include <iostream>
// IN:
// OUT:
#include <cmath>
#define FOR(i, start, end) for (int i = start; i <= end; i++)
using namespace std;

#define MAX 100;
typedef struct
{
    int top;
    int nut[100];
} stack;

stack StackInit()
{
    stack s;
    s.top = -1;
    return s;
}

int StackEmpty(stack s)
{
    return (s.top == -1);
}

int StackFull(stack s)
{
    return (s.top - 1 == 100);
}

void Push(stack *s, int x)
{
    if (StackFull(*s))
    {
        cout << "Full !";
    }
    else
    {
        s->top++;
        s->nut[s->top] = x;
    }
}

int Pop(stack *s)
{
    if(StackEmpty(*s))
    {
        cout << "Nothing!";
    }else
    {
        return  s->nut[s->top--];
    }
}




int main()
{

}

/*

*/