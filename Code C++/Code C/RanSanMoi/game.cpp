#include <iostream>
// #include <graphics.h>
#include "kmin_console.h"
#include <cmath>
using namespace std;

#define FOR(i, start, end) for (int i = start; i <= end; i++)
#define max 100
#define LEN 72
#define XUONG 80
#define TRAI 75
#define PHAI 77

#define T_tren 1
#define T_duoi 21
#define T_trai 1
#define T_phai 55

int snakeLength = 3;
int x = 0, y = 0;

struct Point
{
    int x, y;
    int x0, y0;
} snake[100], direction;

void initSnake()
{
    snake[0].x = T_trai + 4;
    snake[1].x = T_trai + 6;
    snake[2].x = T_trai + 5;
    snake[0].y = snake[1].y = snake[2].y = T_tren + 5;
}

void wall()
{
    for (int i = T_trai; i <= T_phai; i++)
    {
        gotoXY(i, T_tren);
        cout << (char)220;
    }
    for (int i = T_trai; i <= T_phai; i++)
    {
        gotoXY(i, T_duoi);
        cout << (char)220;
    }
    for (int i = T_tren + 1; i <= T_duoi; i++)
    {
        gotoXY(T_trai, i);
        cout << (char)221;
    }
    for (int i = T_tren + 1; i <= T_duoi; i++)
    {
        gotoXY(T_phai, i);
        cout << (char)221;
    }
}

void showSnake(Point lastSnake)
{
    for (int i = 0; i < snakeLength; i++)
    {
        gotoXY(snake[i].x, snake[i].y);
        cout << (char)254;
    }
    gotoXY(lastSnake.x, lastSnake.y);
    cout << " ";
}

Point moveSnake(int arrow)
{
    Point lastSnake = snake[snakeLength - 1];
    for (int i = 0; i < snakeLength; i++)
    {
        if (i == 0)
        {
            snake[0].x0 = snake[0].x;
            snake[0].y0 = snake[0].y;
        }
        else
        {
            snake[i].x0 = snake[i].x;
            snake[i].y0 = snake[i].y;

            snake[i].x = snake[i - 1].x0;
            snake[i].y = snake[i - 1].y0;
        }
    }
    switch (arrow)
    {
    case LEN:
        snake[0].y--;
        break;
    case XUONG:
        snake[0].y++;
        break;
    case PHAI:
        snake[0].x++;
        break;
    case TRAI:
        snake[0].x--;
        break;
    }
    return lastSnake;
}

void keyPress(int &arrow)
{
    int key = inputKey();

    if (key == 'w' || key == 'W' || key == KEY_UP)
    {
        arrow = LEN;
    }
    else if (key == 's' || key == 'S' || key == KEY_DOWN)
    {
        arrow = XUONG;
    }
    else if (key == 'a' || key == 'A' || key == KEY_LEFT)
    {
        arrow = TRAI;
    }
    else if (key == 'd' || key == 'D' || key == KEY_RIGHT)
    {
        arrow = PHAI;
    }
}

bool gameOver()
{
    if (snake[0].y == T_tren || snake[0].y == T_duoi || snake[0].x == T_trai || snake[0].x == T_phai)
    {
        return true;
    }
    return false;
}

Point showFood()
{
    srand((int)time(0));
    int x = T_trai + 1 + rand() % ((T_phai - 1) - (T_trai + 1) + 1);
    int y = T_tren + 1 + rand() % ((T_duoi - 1) - (T_tren + 1) + 1);
    gotoXY(x, y);
    cout << "*";
    return Point{x, y};
}

bool isfood(Point showFood)
{
    if (snake[0].x == showFood.x && snake[0].y == showFood.y)
    {
        snakeLength++;
        return true;
    }
    return false;
}

void score()
{

}

int main()
{
    int arrow = PHAI;
    clrscr();
    initSnake();
    wall();
    Point food = showFood();

    while (1)
    {

        showSnake(moveSnake(arrow));
        keyPress(arrow);
        if (gameOver())
        {
            break;
        }
        if (isfood(food))
        {
            food = showFood();
        }
        Sleep(200);
    }
    clrscr();
    cout << "game over ";
}

/*

*/