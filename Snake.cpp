#include <iostream>
#include <conio.h>
#include <windows.h>

bool game_over;
const int width = 60;
const int height = 30;
int x, y, fruitX, fruitY; //координаты змеи и фруктов
int score; //общий счет игры
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
int tailX[100], tailY[100];
int nTail;

void SetUp() {
    game_over = false;
    dir = STOP;
    x = width / 2 - 1;
    y = height / 2 - 1;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() {
    system("cls");
    COORD cursorPos;
    cursorPos.X = 0;
    cursorPos.Y = 0;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hStdOut, cursorPos);
    for (int i = 0; i < width + 1; i++) {
        std::cout << "#";
    }
    std::cout << std::endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1) {
                std::cout << "#";
            }
            if (i == y && j == x) {
                std::cout << "0";
            }
            else if (i == fruitY && j == fruitX) {
                std::cout << "F";
            }
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        print = true;
                        std::cout << 'o';
                    }
                }
                if (!print) {
                    std::cout << " ";
                }
            }
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < width + 1; i++) {
        std::cout << "#";
    }
    std::cout << std::endl;
    std::cout << "SCORE: " << score << std::endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            game_over = true;
            break;
        }
    }
}

void Logic() {

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
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
    }

    if( x > width || x < 0 || y > height || y < 0){
        game_over = true;
    }

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            game_over = true;
        }
    }

    if (x == fruitX && y == fruitY) {
        score++;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main()
{
    SetUp();
    while (!game_over) {
        Draw();
        Input();
        Logic();
        Sleep(150);
    }

    return 0;
}
