#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct name1
{
	int a;
	int b;
} n1;

void test_1(name1 _x)
{
	_x.a = 2;
	_x.b = 3;
}

void test_2(name1 *_y)
{
	_y->a = 4;
	_y->b = 5;
}

void printf_struct(name1 _z)
{
	printf("%d %d\n", _z.a, _z.b);
}

int main()
{
	name1 te;
	test_1(te);
	printf_struct(te);

	test_2(&te);
	printf_struct(te);
	return 0;
}