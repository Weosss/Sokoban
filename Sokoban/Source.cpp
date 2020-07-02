﻿#include <stdio.h>
#include <curses.h>
#include <stdio.h>


#define WINDOW_WIDTH 79
#define WINDOW_HEIGHT 23
#define WIDTH 12
#define HEIGHT 8

enum dir { up, down, left, right } movement;
int plX, plY;
int step = 0;
int level;
char bufch[8][12];
int xcount;
int win = 0;

char level1[8][12] =
{

    {'#', '#', '#', '#', '#', '#', '#', '#', '#','#','#', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ',' ', '#'},
    {'#', ' ', ' ', ' ', ' ', 'U', 'P', ' ', ' ',' ',' ', '#'},
    {'#', ' ', ' ', 'x', ' ', ' ', 'U', ' ', ' ',' ',' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', 'x', '#', ' ',' ',' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ',' ',' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ',' ',' ', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#','#','#', '#'}

};
char level2[8][12] =
{

    {'#', '#', '#', '#', '#', '#', '#', '#', '#','#','#', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ',' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ',' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ',' ', '#'},
    {'#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ',' ',' ', '#'},
    {'#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ',' ',' ', '#'},
    {'#', 'P', ' ', ' ', ' ', '#', ' ', ' ', ' ',' ',' ', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#','#','#', '#'}
};

void setup()
{
    int tmp = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (level1[i][j] == 'P')
            {
                plY = i;
                plX = j;
            }
        }
    }
}


void printMap()
{
    int localX, localY;
    localX = (WINDOW_WIDTH - WIDTH) / 2;
    localY = (WINDOW_HEIGHT - HEIGHT) / 2;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            const char tmpCh = level1[i][j];
            mvprintw(i + localY, j + localX, &tmpCh);
        }
    }
}



void game()
{
    switch (movement)
    {
    case left:
        if (level1[plY][plX - 1] != '#' && level1[plY][plX - 1] != 'Q')
        {
            if (level1[plY][plX - 1] == 'U' && level1[plY][plX - 2] == 'x')
            {
                level1[plY][plX - 2] = 'Q';
                level1[plY][plX] = ' ';
                level1[plY][plX - 1] = 'P';
                plX--;
                step++;
                win++;
            }
            else if (level1[plY][plX - 1] == 'U' && level1[plY][plX - 2] != '#' && xcount == 0)
            {
                level1[plY][plX - 2] = 'U';
                level1[plY][plX - 1] = ' ';
                level1[plY][plX] = ' ';
                level1[plY][plX - 1] = 'P';
                plX--;
                step++;
            }
            else if (level1[plY][plX - 1] == 'U' && level1[plY][plX - 2] != '#' && xcount == 1)
            {
                level1[plY][plX - 2] = 'U';
                level1[plY][plX - 1] = ' ';
                level1[plY][plX] = 'x';
                level1[plY][plX - 1] = 'P';
                plX--;
                step++;
                xcount--;
            }

            else if (level1[plY][plX - 1] == 'x')
            {
                xcount++;
                level1[plY][plX] = ' ';
                level1[plY][plX - 1] = 'P';
                plX--;
                step++;
            }
            else if (level1[plY][plX - 1] != 'U' && xcount == 0)
            {
                level1[plY][plX] = ' ';
                level1[plY][plX - 1] = 'P';
                plX--;
                step++;
            }
            else if (level1[plY][plX - 1] != 'U' && xcount == 1)
            {
                level1[plY][plX] = 'x';
                level1[plY][plX - 1] = 'P';
                plX--;
                step++;
                xcount--;
            }
        }
        break;

    case right:
        if (level1[plY][plX + 1] != '#' && level1[plY][plX + 1] != 'Q')
        {
            if (level1[plY][plX + 1] == 'U' && level1[plY][plX + 2] == 'x')
            {
                level1[plY][plX + 2] = 'Q';
                level1[plY][plX] = ' ';
                level1[plY][plX + 1] = 'P';
                plX++;
                step++;
                win++;
            }
            else if (level1[plY][plX + 1] == 'U' && level1[plY][plX + 2] != '#' && xcount == 0)
            {
                level1[plY][plX + 2] = 'U';
                level1[plY][plX + 1] = ' ';
                level1[plY][plX] = ' ';
                level1[plY][plX + 1] = 'P';
                plX++;
                step++;
            }
            else if (level1[plY][plX + 1] == 'U' && level1[plY][plX + 2] != '#' && xcount == 1)
            {
                level1[plY][plX + 2] = 'U';
                level1[plY][plX + 1] = ' ';
                level1[plY][plX] = 'x';
                level1[plY][plX + 1] = 'P';
                plX++;
                step++;
                xcount--;
            }
            else if (level1[plY][plX + 1] == 'x')
            {
                xcount++;
                level1[plY][plX] = ' ';
                level1[plY][plX + 1] = 'P';
                plX++;
                step++;
            }
            else if (level1[plY][plX + 1] != 'U' && xcount == 0)
            {
                level1[plY][plX] = ' ';
                level1[plY][plX + 1] = 'P';
                plX++;
                step++;
            }
            else if (level1[plY][plX + 1] != 'U' && xcount == 1)
            {
                level1[plY][plX] = 'x';
                level1[plY][plX + 1] = 'P';
                plX++;
                step++;
                xcount--;
            }
        }
        break;
    case up:
        if (level1[plY - 1][plX] != '#' && level1[plY - 1][plX] != 'Q')
        {
            if (level1[plY - 1][plX] == 'U' && level1[plY - 2][plX] == 'x')
            {
                level1[plY - 2][plX] = 'Q';
                level1[plY][plX] = ' ';
                level1[plY - 1][plX] = 'P';
                plY--;
                step++;
                win++;
            }
            else if (level1[plY - 1][plX] == 'U' && level1[plY - 2][plX] != '#' && xcount == 0)
            {
                level1[plY - 2][plX] = 'U';
                level1[plY - 1][plX] = ' ';
                level1[plY][plX] = ' ';
                level1[plY - 1][plX] = 'P';
                plY--;
                step++;
            }
            else if (level1[plY - 1][plX] == 'U' && level1[plY - 2][plX] != '#' && xcount == 1)
            {
                level1[plY - 2][plX] = 'U';
                level1[plY - 1][plX] = ' ';
                level1[plY][plX] = 'x';
                level1[plY - 1][plX] = 'P';
                plY--;
                step++;
                xcount--;
            }
            else if (level1[plY - 1][plX] == 'x')
            {
                xcount++;
                level1[plY][plX] = ' ';
                level1[plY - 1][plX] = 'P';
                plY--;
                step++;
            }
            else if (level1[plY - 1][plX] != 'U' && xcount == 0)
            {
                level1[plY][plX] = ' ';
                level1[plY - 1][plX] = 'P';
                plY--;
                step++;
            }
            else if (level1[plY - 1][plX] != 'U' && xcount == 1)
            {
                level1[plY][plX] = 'x';
                level1[plY - 1][plX] = 'P';
                plY--;
                step++;
                xcount--;
            }
        }
        break;
    case down:
        if (level1[plY + 1][plX] != '#' && level1[plY + 1][plX] != 'Q')
        {
            if (level1[plY + 1][plX] == 'U' && level1[plY + 2][plX] == 'x')
            {
                level1[plY + 2][plX] = 'Q';
                level1[plY][plX] = ' ';
                level1[plY + 1][plX] = 'P';
                plY++;
                step++;
                win++;
            }
            else if (level1[plY + 1][plX] == 'U' && level1[plY + 2][plX] != '#' && xcount == 0)
            {
                level1[plY + 2][plX] = 'U';
                level1[plY + 1][plX] = ' ';
                level1[plY][plX] = ' ';
                level1[plY + 1][plX] = 'P';
                plY++;
                step++;
            }
            else if (level1[plY + 1][plX] == 'U' && level1[plY + 2][plX] != '#' && xcount == 1)
            {
                level1[plY + 2][plX] = 'U';
                level1[plY + 1][plX] = ' ';
                level1[plY][plX] = 'x';
                level1[plY + 1][plX] = 'P';
                plY++;
                step++;
                xcount--;
            }
            else if (level1[plY + 1][plX] == 'x')
            {
                xcount++;
                level1[plY][plX] = ' ';
                level1[plY + 1][plX] = 'P';
                plY++;
                step++;
            }
            else if (level1[plY + 1][plX] != 'U' && xcount == 0)
            {
                level1[plY][plX] = ' ';
                level1[plY + 1][plX] = 'P';
                plY++;
                step++;
            }
            else if (level1[plY + 1][plX] != 'U' && xcount == 1)
            {
                level1[plY][plX] = 'x';
                level1[plY + 1][plX] = 'P';
                plY++;
                step++;
                xcount--;
            }
        }
        break;
    }
    refresh();
}

int main() {
    printf("Choose lvl: ");
    mvprintw(0, 0, "Game end");
    bool Gg = false;
    initscr();
    curs_set(0);
    noecho();
    setup();
    while (!Gg) {
        mvprintw(0, 0, "Boxes to win: %d", win);
        mvprintw(0, 15, "/3");
        mvprintw(1, 0, "Steps: %d", step);
        printMap();
        int ch = getch();
        if (ch == 'w') movement = up;
        if (ch == 's') movement = down;
        if (ch == 'a') movement = left;
        if (ch == 'd') movement = right;
        if (ch == 'e') Gg = true;
        game();
    }
    erase();
    mvprintw(WINDOW_HEIGHT / 2, WINDOW_WIDTH / 3, "Game end. Your quantity of steps: %d", step);
    refresh();
    getch();
    endwin();
    return 0;
}