#include <iostream>
#include <windows.h>
#include <fstream>
#include <ctime>
#include <conio.h>
#include <math.h>
using namespace std;

void header(HANDLE h);
void clear_screen();
void help(HANDLE h);
void gotoxy(int x, int y);
void load(char maze[][100], string path, int row, int col);
void print(char maze[][100], int row, int col, HANDLE h);
bool moveLeft(char maze[][100], int px, int py, HANDLE h);
bool moveRight(char maze[][100], int px, int py, HANDLE h);
bool moveup(char maze[][100], int px, int py, HANDLE h);
bool movedown(char maze[][100], int px, int py, HANDLE h);
void fire(char maze[][100], int px, int py, HANDLE h);
void firemove(char maze[][100], int row, int col, HANDLE h);
int enemyDirection();
int enemy0Direction();

main()
{
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    char maze[30][100];
    string path = "maze.txt";
    int row = sizeof(maze) / sizeof(maze[0]);
    int col = sizeof(maze[0]) / sizeof(maze[0][0]);

    load(maze, path, row, col);

    bool gameplay = 0;
    string op = " ";
    int px = 15;
    int py = 5;

    int px2 = 15;
    int score1 = 0;
    int score2 = 0;
    int py2 = 95;
    maze[px2][py2] = '0';
    int life1 = 3, life2 = 3;

    int Ecount = 0;
    int ex = 3;
    int ey = 48;

    while (op != "3")
    {
        header(h);
        cout << "1.PLAY" << endl;
        cout << "2.HELP" << endl;
        cout << "3.EXIT" << endl;
        cin >> op;

        if (op == "1")
        {
            op == " ";
            string op2 = " ";

            while (op2 != "3")
            {

                header(h);
                cout << "1.MULTIPLAYER " << endl;
                cout << "2.PLAY WITH COMPUTER" << endl;
                cout << "3.EXIT" << endl;
                // cout << life1 << "   " << life2 << endl;
                cin >> op2;

                if (op2 == "1" || op2 == "2")
                {

                    px = 15;
                    py = 5;

                    px2 = 15;
                    py2 = 95;
                    maze[px][py] = 'O';
                    maze[px2][py2] = '0';

                    Ecount = 0;
                    ex = 3;
                    ey = 48;

                    life1=6;
                    life2=6;
                    gameplay = 0;
                    print(maze, row, col, h);

                    while (gameplay != 1)
                    {
                        gameplay = 0;
                        Sleep(50);
                        bool check;

                        if (GetAsyncKeyState(0x41))
                        {
                            check = moveLeft(maze, px, py, h);
                            if (check == 1)
                            {
                                SetConsoleTextAttribute(h, 10);
                                maze[px][py] = ' ';
                                gotoxy(py, px);
                                cout << ' ';
                                py = py - 1;
                                maze[px][py] = 'O';
                                gotoxy(py, px);
                                cout << maze[px][py];
                            }
                        }
                        if (GetAsyncKeyState(0x53))
                        {
                            check = moveRight(maze, px, py, h);
                            if (check == 1)
                            {
                                SetConsoleTextAttribute(h, 10);
                                maze[px][py] = ' ';
                                gotoxy(py, px);
                                cout << " ";
                                py = py + 1;
                                maze[px][py] = 'O';
                                gotoxy(py, px);
                                cout << maze[px][py];
                            }
                        }
                        if (GetAsyncKeyState(0x57))
                        {
                            check = moveup(maze, px, py, h);
                            if (check == 1)
                            {
                                SetConsoleTextAttribute(h, 10);
                                maze[px][py] = ' ';
                                gotoxy(py, px);
                                cout << ' ';
                                px = px - 1;
                                maze[px][py] = 'O';
                                gotoxy(py, px);
                                cout << maze[px][py];
                            }
                        }
                        if (GetAsyncKeyState(0x5A))
                        {
                            check = movedown(maze, px, py, h);
                            if (check == 1)
                            {
                                SetConsoleTextAttribute(h, 10);
                                maze[px][py] = ' ';
                                gotoxy(py, px);
                                cout << ' ';
                                px = px + 1;
                                maze[px][py] = 'O';
                                gotoxy(py, px);
                                cout << maze[px][py];
                            }
                        }
                        if (GetAsyncKeyState(0x46))
                        {
                            SetConsoleTextAttribute(h, 2);
                            if (maze[px][py + 1] == ' ')
                            {
                                maze[px][py + 1] = '.';
                                gotoxy(py + 1, px);
                                cout << maze[px][py + 1];
                            }
                        }
                        //=======================P1 FIRE MOVE

                        for (int i = row - 1; i > 0; i--)
                        {
                            for (int j = col; j > 0; j--)
                            {

                                if (maze[i][j] == '.')
                                {

                                    maze[i][j] = ' ';
                                    gotoxy(j, i);
                                    cout << maze[i][j];
                                    if (maze[i][j + 1] == '0' || maze[i][j + 1] == 'E')
                                    {
                                        if (maze[i][j + 1] == '0')
                                        {
                                            life2--;
                                        }
                                        if (maze[i][j + 1] == 'E')
                                        {
                                            maze[ex][ey] = ' ';
                                            score1++;
                                            ex = 3;
                                            ey = 48;
                                        }
                                    }

                                    if (maze[i][j + 1] == ' ')
                                    {
                                        maze[i][j + 1] = '.';
                                        gotoxy(j + 1, i);
                                        cout << maze[i][j + 1];
                                    }
                                }
                            }
                        }

                        //--------------------------------------------------player 2-------------------------------------------------------------------
                        //---------------------------------------------------left
                        if (op2 == "1")
                        {

                            if (GetAsyncKeyState(VK_LEFT))
                            {

                                if (maze[px2][py2 - 1] == ' ')
                                {
                                    SetConsoleTextAttribute(h, 4);
                                    maze[px2][py2] = ' ';
                                    gotoxy(py2, px2);
                                    cout << ' ';
                                    py2 = py2 - 1;
                                    maze[px2][py2] = 'O';
                                    gotoxy(py2, px2);
                                    cout << maze[px2][py2];
                                }
                            }
                            if (GetAsyncKeyState(VK_RIGHT))
                            {
                                if (maze[px2][py2 + 1] == ' ')
                                {
                                    SetConsoleTextAttribute(h, 4);
                                    maze[px2][py2] = ' ';
                                    gotoxy(py2, px2);
                                    cout << " ";
                                    py2 = py2 + 1;
                                    maze[px2][py2] = 'O';
                                    gotoxy(py2, px2);
                                    cout << maze[px2][py2];
                                }
                            }
                            if (GetAsyncKeyState(VK_UP))
                            {
                                if (maze[px2 - 1][py2] == ' ')
                                {
                                    SetConsoleTextAttribute(h, 4);
                                    maze[px2][py2] = ' ';
                                    gotoxy(py2, px2);
                                    cout << ' ';
                                    px2 = px2 - 1;
                                    maze[px2][py2] = 'O';
                                    gotoxy(py2, px2);
                                    cout << maze[px2][py2];
                                }
                            }
                            if (GetAsyncKeyState(VK_DOWN))
                            {
                                if (maze[px2 + 1][py2] == ' ')
                                {
                                    SetConsoleTextAttribute(h, 4);
                                    maze[px2][py2] = ' ';
                                    gotoxy(py2, px2);
                                    cout << ' ';
                                    px2 = px2 + 1;
                                    maze[px2][py2] = 'O';
                                    gotoxy(py2, px2);
                                    cout << maze[px2][py2];
                                }
                            }
                            if (GetAsyncKeyState(VK_SPACE))
                            {
                                SetConsoleTextAttribute(h, 2);
                                if (maze[px2][py2 - 1] == ' ')
                                {
                                    maze[px2][py2 - 1] = '-';
                                    gotoxy(py2 - 1, px2);
                                    cout << maze[px2][py2 - 1];
                                }
                            }
                            //=======================P1 FIRE MOVE
                        }

                        // -------------------------------------------COMPUTER PLAYER

                        if (op2 == "2")
                        {
                            int rom = enemy0Direction();
                            if (rom == 1)
                            {
                                if (maze[px2][py2 - 1] == ' ')
                                {
                                    SetConsoleTextAttribute(h, 14);
                                    maze[px2][py2] = ' ';
                                    gotoxy(py2, px2);
                                    cout << ' ';
                                    py2 = py2 - 1;
                                    maze[px2][py2] = '0';
                                    gotoxy(py2, px2);
                                    cout << maze[px2][py2];
                                }
                            }
                            else if (rom == 2)
                            {
                                if (maze[px2][py2 + 1] == ' ')
                                {
                                    SetConsoleTextAttribute(h, 14);
                                    maze[px2][py2] = ' ';
                                    gotoxy(py2, px2);
                                    cout << ' ';
                                    py2 = py2 + 1;
                                    maze[px2][py2] = '0';
                                    gotoxy(py2, px2);
                                    cout << maze[px2][py2];
                                }
                            }
                            else if (rom == 3)
                            {
                                if (maze[px2 + 1][py2] == ' ')
                                {
                                    SetConsoleTextAttribute(h, 14);
                                    maze[px2][py2] = ' ';
                                    gotoxy(py2, px2);
                                    cout << ' ';
                                    px2 = px2 + 1;
                                    maze[px2][py2] = '0';
                                    gotoxy(py2, px2);
                                    cout << maze[px2][py2];
                                }
                            }
                            else if (rom == 4)
                            {
                                if (maze[px2 - 1][py2] == ' ')
                                {
                                    SetConsoleTextAttribute(h, 14);
                                    maze[px2][py2] = ' ';
                                    gotoxy(py2, px2);
                                    cout << ' ';
                                    px2 = px2 - 1;
                                    maze[px2][py2] = '0';
                                    gotoxy(py2, px2);
                                    cout << maze[px2][py2];
                                }
                            }
                            if (maze[px2][py2 - 5] == 'O' || maze[px2][py2 - 4] == 'O' || maze[px2][py2 - 3] == 'O' || maze[px2][py2 - 2] == 'O' || maze[px2][py2 - 1] == 'O')
                            {
                                SetConsoleTextAttribute(h, 2);

                                maze[px2][py2 - 1] = '-';
                                gotoxy(py2 - 1, px2);
                                cout << maze[px2][py2 - 1];
                            }
                            if (maze[px2][py2 + 5] == 'O' || maze[px2][py2 + 4] == 'O' || maze[px2][py2 + 3] == 'O' || maze[px2][py2 + 2] == 'O' || maze[px2][py2 + 1] == 'O' || maze[px2][py2 + 5] == '0' || maze[px2][py2 + 4] == '0' || maze[px2][py2 + 3] == '0' || maze[px2][py2 + 2] == '0' || maze[px2][py2 + 1] == '0')
                            {
                                maze[px2][py2 + 1] = '.';
                                gotoxy(py2 + 1, px2);
                                cout << maze[px2][py2 + 1];
                            }
                        }

                        //--------------------------fire move--------------------------------------------------------
                        for (int i = 0; i < row - 1; i++)
                        {
                            for (int j = 0; j < col; j++)
                            {

                                if (maze[i][j] == '-')
                                {

                                    maze[i][j] = ' ';
                                    gotoxy(j, i);
                                    cout << maze[i][j];
                                    if (maze[i][j - 1] == 'O')
                                    {
                                        life1--;
                                    }
                                    if (maze[i][j - 1] == 'E')
                                    {
                                        maze[ex][ey] = ' ';
                                        score2++;
                                        ex = 3;
                                        ey = 48;
                                    }
                                    if (maze[i][j - 1] == '0')
                                    {
                                        life2--;
                                    }

                                    if (maze[i][j - 1] == ' ')
                                    {
                                        maze[i][j - 1] = '-';
                                        gotoxy(j - 1, i);
                                        cout << maze[i][j - 1];
                                    }
                                }
                            }
                        }
                        gotoxy(80, 31);
                        cout << "P2 LIFE : " << life2;
                        gotoxy(0, 31);
                        cout << "P1 LIFE : " << life1;

                        for (int i = 0; i < row; i++)
                        {
                            for (int j = 0; j < col; j++)
                            {
                                if (maze[i][j] == 'E')
                                {
                                    Ecount++;
                                }
                            }
                        }

                        //------------------------ENEMY-------------------------------------------------------------------------------

                        if (Ecount == 0)
                        {
                            maze[ex][ey] = 'E';
                        }
                        int rom = enemyDirection();
                        if (rom == 1)
                        {
                            if (maze[ex][ey - 1] == ' ')
                            {
                                SetConsoleTextAttribute(h, 14);
                                maze[ex][ey] = ' ';
                                gotoxy(ey, ex);
                                cout << ' ';
                                ey = ey - 1;
                                maze[ex][ey] = 'E';
                                gotoxy(ey, ex);
                                cout << maze[ex][ey];
                            }
                        }
                        else if (rom == 2)
                        {
                            if (maze[ex][ey + 1] == ' ')
                            {
                                SetConsoleTextAttribute(h, 14);
                                maze[ex][ey] = ' ';
                                gotoxy(ey, ex);
                                cout << ' ';
                                ey = ey + 1;
                                maze[ex][ey] = 'E';
                                gotoxy(ey, ex);
                                cout << maze[ex][ey];
                            }
                        }
                        else if (rom == 3)
                        {
                            if (maze[ex + 1][ey] == ' ')
                            {
                                SetConsoleTextAttribute(h, 14);
                                maze[ex][ey] = ' ';
                                gotoxy(ey, ex);
                                cout << ' ';
                                ex = ex + 1;
                                maze[ex][ey] = 'E';
                                gotoxy(ey, ex);
                                cout << maze[ex][ey];
                            }
                        }
                        else if (rom == 4)
                        {
                            if (maze[ex - 1][ey] == ' ')
                            {
                                SetConsoleTextAttribute(h, 14);
                                maze[ex][ey] = ' ';
                                gotoxy(ey, ex);
                                cout << ' ';
                                ex = ex - 1;
                                maze[ex][ey] = 'E';
                                gotoxy(ey, ex);
                                cout << maze[ex][ey];
                            }
                        }

                        if (maze[ex][ey - 5] == 'O' || maze[ex][ey - 4] == 'O' || maze[ex][ey - 3] == 'O' || maze[ex][ey - 2] == 'O' || maze[ex][ey - 1] == 'O' || maze[ex][ey - 5] == '0' || maze[ex][ey - 4] == '0' || maze[ex][ey - 3] == '0' || maze[ex][ey - 2] == '0' || maze[ex][ey - 1] == '0')
                        {
                            SetConsoleTextAttribute(h, 2);
                            if (maze[ex][ey - 1] == ' ')
                            {
                                maze[ex][ey - 1] = '-';
                                gotoxy(ey - 1, ex);
                                cout << maze[ex][ey - 1];
                            }
                        }
                        if (maze[ex][ey + 5] == 'O' || maze[ex][ey + 4] == 'O' || maze[ex][ey + 3] == 'O' || maze[ex][ey + 2] == 'O' || maze[ex][ey + 1] == 'O' || maze[ex][ey + 5] == '0' || maze[ex][ey + 4] == '0' || maze[ex][ey + 3] == '0' || maze[ex][ey + 2] == '0' || maze[ex][ey + 1] == '0')
                        {
                            maze[ex][ey + 1] = '.';
                            gotoxy(ey + 1, ex);
                            cout << maze[ex][ey + 1];
                        }
                        if (GetAsyncKeyState(VK_ESCAPE) || life1 == 0 || life2 == 0)
                        {
                            gameplay = 1; // Stop the game
                            
                        }

                        gotoxy(80, 32);
                        cout << "P2 Score : " << score2;
                        gotoxy(0, 32);
                        cout << "P1 Score : " << score1;
                        if (life1 <= 0)
                        {
                            header(h);
                            
                            cout << "PLAYER 2 WIN THE MATCH" << endl;
                            cout << "WITH SCORE : " << score2 << endl;
                            score2 = 0;
                            clear_screen();
                            life1 = 3;
                            life2 = 3;
                        }
                        if (life2 <= 0)
                        {
                            header(h);
                            
                            cout << "PLAYER 1 WIN THE MATCH" << endl;
                            cout << "WITH SCORE : " << score1 << endl;
                            score1 = 0;
                            clear_screen();

                            getch();
                            life1 = 3;
                            life2 = 3;
                        }
                    }
                }

                else if (op2 != "3")
                {
                    header(h);
                    cout << "ENTER THE VALID OPTION" << endl;
                    clear_screen();
                }

                maze[px2][py2] = ' ';
                maze[px][py] = ' ';
                maze[ex][ey] = ' ';
                Ecount = 0;

                for (int i = 0; i > row - 1; i++)
                {
                    for (int j = 0; j > col; j++)
                    {

                        if (maze[i][j] == '-')
                        {
                            maze[i][j] = ' ';
                        }
                        else if (maze[i][j] == '.')
                        {
                            maze[i][j] = ' ';
                        }
                    }
                }
                // if (life1 <= 0)
                // {
                //     header(h);
                //     cout << "PLAYER 2 WIN THE MATCH" << endl;
                //     cout << "WITH SCORE : " << score2 << endl;
                //     score2 = 0;
                //     life1 = 6;
                //     life2 = 6;
                //     clear_screen();
                    
                // }
                // if (life2 <= 0)
                // {
                //     header(h);
                //     cout << "PLAYER 1 WIN THE MATCH" << endl;
                //     cout << "WITH SCORE : " << score1 << endl;
                //     score1 = 0;
                //     life1 = 6;
                //     life2 = 6;
                //     clear_screen();
                // }
            }
        }

        else if (op == "2")
        {
            header(h);
            help(h);
        }
        else if (op != "3")
        {
            cout << "ENTER THE VALID OPTION" << endl;
            clear_screen();
        }
        if (life1 <= 0)
        {
            header(h);
            clear_screen();
            cout << "PLAYER 2 WIN THE MATCH" << endl;
            cout << "WITH SCORE : " << score2 << endl;
            score2 = 0;
            clear_screen();
            life1 = 3;
            life2 = 3;
        }
        if (life2 <= 0)
        {
            header(h);
            clear_screen();
            cout << "PLAYER 1 WIN THE MATCH" << endl;
            cout << "WITH SCORE : " << score1 << endl;
            score1 = 0;
            clear_screen();

            getch();
            life1 = 3;
            life2 = 3;
        }
    }
}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void load(char maze[][100], string path, int row, int col)
{
    fstream my;
    string record;
    my.open(path, ios::in);
    for (int x = 0; x < row; x++)
    {
        getline(my, record);
        for (int y = 0; y < col; y++)
        {
            maze[x][y] = record[y];
        }
    }
}

void print(char maze[][100], int row, int col, HANDLE h)
{
    system("cls");
    for (int x = 0; x < row; x++)
    {
        for (int y = 0; y < col; y++)
        {
            if (maze[x][y] == '=')
            {
                SetConsoleTextAttribute(h, 1);
                cout << maze[x][y];
            }
            else if (maze[x][y] == '-')
            {
                SetConsoleTextAttribute(h, 3);
                cout << maze[x][y];
            }
            else
            {
                SetConsoleTextAttribute(h, 5);
                cout << maze[x][y];
            }
        }
        cout << endl;
    }
}

bool moveLeft(char maze[][100], int px, int py, HANDLE h)
{
    if (maze[px][py - 1] == ' ')
    {
        return 1;
    }
    return 0;
}

bool moveRight(char maze[][100], int px, int py, HANDLE h)
{
    if (maze[px][py + 1] == ' ')
    {
        return 1;
    }
    return 0;
}

bool moveup(char maze[][100], int px, int py, HANDLE h)
{
    if (maze[px - 1][py] == ' ')
    {
        return 1;
    }
    return 0;
}
bool movedown(char maze[][100], int px, int py, HANDLE h)
{
    if (maze[px + 1][py] == ' ')
    {
        return 1;
    }
    return 0;
}


void clear_screen()
{
    string t="0";
    while(t!="1")
    {cout << endl
         << " PRESS 1 KEY TO CONTINUE ..... " << endl;
         
         cin>>t;
    if (t=="1")
    {
        system("cls");
    }
    }
}

void header(HANDLE h)
{
    system("cls");
    SetConsoleTextAttribute(h, 124);

    cout << "       oooooo   ooooo    ooooo      o   o   ooooooo   ooooo   ooooo     ooooo     " << endl;
    cout << "       o          o      o          o   o      o      o       o   o     o         " << endl;
    cout << "       oooooo     o      o  ooo     ooooo      o      ooooo   ooooo     ooooo     " << endl;
    cout << "       o          o      o  o o     o   o      o      o       o o           o     " << endl;
    cout << "       o        ooooo    ooooo      o   o      o      ooooo   o  o      ooooo     " << endl
         << endl;
    cout << "=====================================================================================" << endl
         << endl
         << endl;
}

void help(HANDLE h)
{
    SetConsoleTextAttribute(h, 232);
    cout << "IN SINGLE PLAYER WITH COMPUTER" << endl;
    cout << "Player will move with LEFT,RIGHT,UP,DOWN key" << endl;
    cout << "For fire press SPACE" << endl;
    cout << "ENEMY also generated from black hole you also need to kill them." << endl;
    cout << "When you kill the enemy you got score" << endl;
    cout << "When you kill the computer player you will win the game." << endl
         << endl;

    cout << "IN MULTI_PLAYER " << endl;
    cout << "Player 1 will move with LEFT,RIGHT,UP,DOWN key" << endl;
    cout << "Player 2 will move with A for LEFT,D for RIGHT,W for UP,X for DOWN key" << endl;
    cout << "For fire player 1 press SPACE" << endl;
    cout << "For fire player 2 press 0" << endl;
    cout << "ENEMY also generated from black hole you also need to kill them." << endl;
    cout << "BOTH got score on killing the enemy" << endl;
    cout << "Who kill first the other player that will win the game" << endl
         << endl;

    clear_screen();
}

int enemyDirection()
{
    srand(time(0));
    int result = 1 + (rand() % 4);
    return result;
}

int enemy0Direction()
{
    srand(time(0));
    int result = 2 + (rand() % 4);
    return result;
}