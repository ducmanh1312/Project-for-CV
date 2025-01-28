#include <iostream>
#include <stdio.h>
using namespace std;

struct Node // khai báo
{
    int data;
    struct Node *next; // link
};
typedef struct Node *listNode;

listNode creatNode(int x)
{
    listNode temp;
    // temp = (listNode)malloc(sizeof(listNode));
    listNode tempt = (listNode) new listNode;
    temp->data = x;
    temp->next = NULL;
    return temp;
}

void Insert_Begin(listNode *head, int x)
{
    listNode p = creatNode(x);
    p->next = *head;
    *head = p;
}

void Insert_End(listNode *head, int x)
{
    listNode temp, p;
    temp = creatNode(x);
    p = *head;

    if (*head == NULL)
    {
        *head = temp;
    }
    else
    {
        while (p->next != NULL)
            p = p->next;
        p->next = temp;
    }
}

void Insert_Mid(listNode *head, int position, int x)
{
    listNode temp, p;
    temp = creatNode(x);
    p = *head;

    if (*head == NULL || position == 0)
        Insert_Begin(head, x);
    else
    {
        int k = 1;
        while (k != position && p->next != NULL)
        {
            p = p->next;
            k++;
        }
        if (k != position)
            cout << " impossible";
        else
        {
            temp->next = p->next;
            p->next = temp;
        }
    }
}

void delHead(listNode *head)
{
    if (*head != NULL)
        *head = (*head)->next;
}

void delEnd(listNode *head)
{
    listNode p = creatNode(NULL);
    p = *head;
    if (*head != NULL)
    {
        if ((*head)->next == NULL)
            delHead(head);
        else
        {
            while (p->next->next != NULL)
            {
                p = p->next;
            }
            p->next = NULL;
        }
    }
}

void delMid(listNode *head, int position)
{
    listNode p = creatNode(NULL);
    p = *head;
    if (*head != NULL)
    {
        if ((*head)->next == NULL)
        {
            if (position == 0)
                delHead(head);

            else
                cout << " Impossible";
        }
        else
        {
            int k = 1;
            while (k != position && p->next->next != NULL)
            {
                p = p->next;
                k++;
            }

            if (k != position)
                cout << " Impossible";
            else
            {
                p->next = p->next->next;
            }
        }
    }
}

int Get(listNode *head, int position)
{
    listNode p = creatNode(NULL);
    p = *head;
    if (*head == NULL)
        return -1;
    else
    {
        int k = 0;
        while (k != position && p->next != NULL)
        {
            p = p->next;
            k++;
        }
        if (k != position)
        {
            return -1;
        }
        else
        {
            return p->data;
        }
    }
}

int Search(listNode *head, int x)
{
    if (*head == NULL)
        return -1;
    else
    {
    }
}
//
//
//

typedef struct
{
    listNode top;
} stack;

stack StackInit()
{
    stack s = (stack) new stack;
    s.top = NULL;
}

int StackEmpty(stack s)
{
    return (s.top == NULL);
}

void Push(stack *s, int x)
{
    listNode p = creatNode(x);
    p->next = s->top;
    s->top = p;
}

int Pop(stack *s)
{
    listNode p = s->top;
    s->top = s->top->next;
    return p->data;
}



main()
{
    cout <<"done";
}