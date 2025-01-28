#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;

typedef struct node
{
    int data;
    node *left;
    node *right;
} *treeNode;

treeNode creatTree(int x)
{
    treeNode temp;
    temp = (treeNode) new treeNode;
    temp->data = x;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

treeNode addTree(node *t, int x)
{
    if (t == NULL)
    {
        t = creatTree(x);
    }
    else
    {
        if (x < t->data)
        {
            t->left = addTree(t->left, x);
        }
        else
        {
            t->right = addTree(t->right, x);
        }
    }
}

void printTree(node *t)
{
    if (t != NULL)
    {
        printTree(t->left);
        cout << t->data << " ";
        printTree(t->right);
    }
}

int countLeafNode(node *t, int temp)
{

    if (t != NULL)
    {
        if (t->left == NULL && t->right == NULL)
            temp++;
        temp = countLeafNode(t->left, temp);
        temp = countLeafNode(t->right, temp);
    }
    return temp;
}

int treeLevel(node *t)
{
    if (t == NULL)
        return -1;
    return 1 + max(treeLevel(t->left), treeLevel(t->right));
}

bool checkAvl(node *t)
{
    if (t == NULL)
        return true;
    if (abs(treeLevel(t->left) - treeLevel(t->right)) > 1)
        return checkAvl(t->left) && checkAvl(t->right);
}

node *insert(node *t, int x)
{
    if (t == NULL)
    {
        node *temp = new node;
        temp->data = x;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }
    else
    {
        if (x < t->data)
        {
            t->left = insert(t->left, x);
        }
        else
        {
            t->right = insert(t->right, x);
        }
    }
}

node *turnRight(node *a)
{
    node *b = a->left;
    node *d = a->right;
    a->left = d;
    b->right = a;
    return b;
}

node *turnLeft(node *a)
{
    node *b = a->right;
    node *c = b->left;
    a->right = c;
    b->left = a;
    return b;
}

node *updateTreeAvl(node *t)
{
    if (!checkAvl(t))
    {
        if (treeLevel(t->left) > treeLevel(t->right))
        {
            node *p = t->left;
            if (treeLevel(t->left) >= treeLevel(t->right))
            {
                t = turnRight(t);
            }
            else
            {
                p = turnLeft(p);
                t = turnRight(t);
            }
        }
        else
        {
            node *p = t->right;
            if (treeLevel(t->right) >= treeLevel(t->left))
            {
                t = turnLeft(t);
            }

            else
            {
                p = turnRight(p);
                t = turnLeft(t);
            }
        }
    }
    if (t->left != NULL)
        t->left = updateTreeAvl(t->left);
    if (t->right != NULL)
        t->right = updateTreeAvl(t->right);

    return t;
}

void deleteTree(node *t, int x)
{
    if(t != NULL)
    {
        if(t->data ==  x) t = NULL;
        deleteNode(t->left);
        deleteNode(t->right);
    }
}

int main(){
	int n, temp, x;
	cin >> n;
	node * t = NULL;
	for (int i = 0; i < n; i++){
		cin >> temp;
		t = addTree(t, temp);
	}
    cin >> x;
    deleteTree(t,x);
    printTree(t);

	return 0;
}