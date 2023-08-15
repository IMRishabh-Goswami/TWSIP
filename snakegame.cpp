#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
bool gameend;
const int width = 20;
const int height = 20;
int x, y, foodX, foodY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;
void Setup()
{
    gameend = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    foodX = rand() % width;
    foodY = rand() % height;
    score = 0;
}
void Tie()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{0,0});
	for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
 
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == foodY && j == foodX)
                cout << "*";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
                 
 
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }
 
    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case KEY_UP:
            dir = UP;
            break;
        case KEY_DOWN:
            dir = DOWN;
            break;
        case KEY_RIGHT:
            dir = RIGHT;
            break;
        case KEY_LEFT:
            dir = LEFT;
            break;
        case 'x':
            gameend = true;
            break;
        }
    }
}
void Approach()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;
 
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameend = true;
 
    if (x == foodX && y == foodY)
    {
        score += 100;
        foodX = rand() % width;
        foodY = rand() % height;
        nTail++;
    }
}
int main()
{
    Setup();
    while (!gameend)
    {
        Tie();
        Input();
        Approach();
       Sleep(50);
    }
    return 0;
}
