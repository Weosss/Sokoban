#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>


#define WIDTH 12
#define HEIGHT 8

enum dir { up, down, left, right } movement;
int plX, plY;
int step = 0;
int xcount;
int win;
void file_open(void);
FILE* level;
char ch;
char bufch[HEIGHT][WIDTH];

int o, p, count = 0;

void file_open(void) 
{
    if ((level = fopen("level.txt", "r")) == NULL)
    {
        fprintf(stdout, "%s\n", "Cant read lvl file ");
        exit(EXIT_FAILURE);
    }
}

void setup()
{

    int tmp = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (bufch[i][j] == 'P')
            {
                plY = i;
                plX = j;
            }
        }
    }
}


void printMap()
{
    erase();
    int x, y;
    int xn, yn;
    x = getmaxx(stdscr);
    y = getmaxy(stdscr);
    xn = (x / 2) - (WIDTH / 2);
    yn = (y / 2) - (HEIGHT / 2);
    mvprintw(0, 0, "Boxes to win: %d", win);
    mvprintw(0, 15, "/3");
    mvprintw(1, 0, "Steps: %d", step);
    mvprintw(0, xn, "Move - wasd. Exit - e.");
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            const char tmpCh = bufch[i][j];
            mvprintw(i + yn, j + xn, &tmpCh);
        }
    }
}



void game()
{
    switch (movement)
    {
    case left:
        if (bufch[plY][plX - 1] != '#' && bufch[plY][plX - 1] != 'Q')
        {
            if (bufch[plY][plX - 1] == 'U' && bufch[plY][plX - 2] == 'x')
            {
                bufch[plY][plX - 2] = 'Q';
                bufch[plY][plX] = ' ';
                bufch[plY][plX - 1] = 'P';
                plX--;
                step++;
                win++;
            }
            else if (bufch[plY][plX - 1] == 'U' && bufch[plY][plX - 2] != '#' && xcount == 0 && bufch[plY][plX - 2] != 'U' && bufch[plY][plX - 2] != 'Q')
            {
                bufch[plY][plX - 2] = 'U';
                bufch[plY][plX] = ' ';
                bufch[plY][plX - 1] = 'P';
                plX--;
                step++;
            }
            else if (bufch[plY][plX - 1] == 'U' && bufch[plY][plX - 2] != '#' && xcount == 1 && bufch[plY][plX - 2] != 'U' && bufch[plY][plX - 2] != 'Q')
            {
                bufch[plY][plX - 2] = 'U';
                bufch[plY][plX - 1] = ' ';
                bufch[plY][plX] = 'x';
                bufch[plY][plX - 1] = 'P';
                plX--;
                step++;
                xcount--;
            }

            else if (bufch[plY][plX - 1] == 'x')
            {
                xcount++;
                bufch[plY][plX] = ' ';
                bufch[plY][plX - 1] = 'P';
                plX--;
                step++;
            }
            else if (bufch[plY][plX - 1] != 'U' && xcount == 0)
            {
                bufch[plY][plX] = ' ';
                bufch[plY][plX - 1] = 'P';
                plX--;
                step++;
            }
            else if (bufch[plY][plX - 1] != 'U' && xcount == 1)
            {
                bufch[plY][plX] = 'x';
                bufch[plY][plX - 1] = 'P';
                plX--;
                step++;
                xcount--;
            }
        }
        break;

    case right:
        if (bufch[plY][plX + 1] != '#' && bufch[plY][plX + 1] != 'Q')
        {
            if (bufch[plY][plX + 1] == 'U' && bufch[plY][plX + 2] == 'x')
            {
                bufch[plY][plX + 2] = 'Q';
                bufch[plY][plX] = ' ';
                bufch[plY][plX + 1] = 'P';
                plX++;
                step++;
                win++;
            }
            else if (bufch[plY][plX + 1] == 'U' && bufch[plY][plX + 2] != '#' && xcount == 0 && bufch[plY][plX + 2] != 'U' && bufch[plY][plX + 2] != 'Q')
            {
                bufch[plY][plX + 2] = 'U';
                bufch[plY][plX + 1] = ' ';
                bufch[plY][plX] = ' ';
                bufch[plY][plX + 1] = 'P';
                plX++;
                step++;
            }
            else if (bufch[plY][plX + 1] == 'U' && bufch[plY][plX + 2] != '#' && xcount == 1 && bufch[plY][plX + 2] != 'U' && bufch[plY][plX + 2] != 'Q')
            {
                bufch[plY][plX + 2] = 'U';
                bufch[plY][plX + 1] = ' ';
                bufch[plY][plX] = 'x';
                bufch[plY][plX + 1] = 'P';
                plX++;
                step++;
                xcount--;
            }
            else if (bufch[plY][plX + 1] == 'x')
            {
                xcount++;
                bufch[plY][plX] = ' ';
                bufch[plY][plX + 1] = 'P';
                plX++;
                step++;
            }
            else if (bufch[plY][plX + 1] != 'U' && xcount == 0)
            {
                bufch[plY][plX] = ' ';
                bufch[plY][plX + 1] = 'P';
                plX++;
                step++;
            }
            else if (bufch[plY][plX + 1] != 'U' && xcount == 1)
            {
                bufch[plY][plX] = 'x';
                bufch[plY][plX + 1] = 'P';
                plX++;
                step++;
                xcount--;
            }
        }
        break;
    case up:
        if (bufch[plY - 1][plX] != '#' && bufch[plY - 1][plX] != 'Q')
        {
            if (bufch[plY - 1][plX] == 'U' && bufch[plY - 2][plX] == 'x')
            {
                bufch[plY - 2][plX] = 'Q';
                bufch[plY][plX] = ' ';
                bufch[plY - 1][plX] = 'P';
                plY--;
                step++;
                win++;
            }
            else if (bufch[plY - 1][plX] == 'U' && bufch[plY - 2][plX] != '#' && xcount == 0 && bufch[plY - 2][plX] != 'U' && bufch[plY - 2][plX] != 'Q')
            {
                bufch[plY - 2][plX] = 'U';
                bufch[plY - 1][plX] = ' ';
                bufch[plY][plX] = ' ';
                bufch[plY - 1][plX] = 'P';
                plY--;
                step++;
            }
            else if (bufch[plY - 1][plX] == 'U' && bufch[plY - 2][plX] != '#' && xcount == 1 && bufch[plY - 2][plX] != 'U' && bufch[plY - 2][plX] != 'Q')
            {
                bufch[plY - 2][plX] = 'U';
                bufch[plY - 1][plX] = ' ';
                bufch[plY][plX] = 'x';
                bufch[plY - 1][plX] = 'P';
                plY--;
                step++;
                xcount--;
            }
            else if (bufch[plY - 1][plX] == 'x')
            {
                xcount++;
                bufch[plY][plX] = ' ';
                bufch[plY - 1][plX] = 'P';
                plY--;
                step++;
            }
            else if (bufch[plY - 1][plX] != 'U' && xcount == 0)
            {
                bufch[plY][plX] = ' ';
                bufch[plY - 1][plX] = 'P';
                plY--;
                step++;
            }
            else if (bufch[plY - 1][plX] != 'U' && xcount == 1)
            {
                bufch[plY][plX] = 'x';
                bufch[plY - 1][plX] = 'P';
                plY--;
                step++;
                xcount--;
            }
        }
        break;
    case down:
        if (bufch[plY + 1][plX] != '#' && bufch[plY + 1][plX] != 'Q')
        {
            if (bufch[plY + 1][plX] == 'U' && bufch[plY + 2][plX] == 'x')
            {
                bufch[plY + 2][plX] = 'Q';
                bufch[plY][plX] = ' ';
                bufch[plY + 1][plX] = 'P';
                plY++;
                step++;
                win++;
            }
            else if (bufch[plY + 1][plX] == 'U' && bufch[plY + 2][plX] != '#' && xcount == 0 && bufch[plY + 2][plX] != 'U' && bufch[plY + 2][plX] != 'Q')
            {
                bufch[plY + 2][plX] = 'U';
                bufch[plY + 1][plX] = ' ';
                bufch[plY][plX] = ' ';
                bufch[plY + 1][plX] = 'P';
                plY++;
                step++;
            }
            else if (bufch[plY + 1][plX] == 'U' && bufch[plY + 2][plX] != '#' && xcount == 1 && bufch[plY + 2][plX] != 'U' && bufch[plY + 2][plX] != 'Q')
            {
                bufch[plY + 2][plX] = 'U';
                bufch[plY + 1][plX] = ' ';
                bufch[plY][plX] = 'x';
                bufch[plY + 1][plX] = 'P';
                plY++;
                step++;
                xcount--;
            }
            else if (bufch[plY + 1][plX] == 'x')
            {
                xcount++;
                bufch[plY][plX] = ' ';
                bufch[plY + 1][plX] = 'P';
                plY++;
                step++;
            }
            else if (bufch[plY + 1][plX] != 'U' && xcount == 0)
            {
                bufch[plY][plX] = ' ';
                bufch[plY + 1][plX] = 'P';
                plY++;
                step++;
            }
            else if (bufch[plY + 1][plX] != 'U' && xcount == 1)
            {
                bufch[plY][plX] = 'x';
                bufch[plY + 1][plX] = 'P';
                plY++;
                step++;
                xcount--;
            }
        }
        break;
    }
    refresh();
}

int main(int agrc, char* argv[]) {
    int x, y;
    int xn, yn;
    x = getmaxx(stdscr);
    y = getmaxy(stdscr);
    xn = (x / 2) - (WIDTH / 2);
    yn = (y / 2) - (HEIGHT / 2);
    file_open();
    for (o = 0; o < HEIGHT; ++o) 
    {
        for (p = 0; (ch = getc(level)) != '\n' && (ch != EOF); ++p)
        {
            bufch[o][p] = ch; 
        } 
        if (ch == EOF) 
        {
            break;
        } 
        else 
        {
            bufch[o][p] = '\0';
            ++count;
        }

    } // конец внешнего for
    fclose(level);
    mvprintw(0, 0, "Game end");
    initscr();
    curs_set(0);
    noecho();
    setup();
    while (win != 3) {
        printMap();
        int ch = getch();
        if (ch == 'w') movement = up;
        if (ch == 's') movement = down;
        if (ch == 'a') movement = left;
        if (ch == 'd') movement = right;
        if (ch == 'e') win = 3;
        game();
    }
    erase();
    mvprintw(10, 20, "Game end. Your quantity of steps: %d", step);
    refresh();
    getch();
    endwin();
    return 0;
}