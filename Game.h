#ifndef GAME_H
#define GAME_H

#include "IMG.h"

#include <cstdio>
#include <cstdlib>
#include <ctime>

namespace Game
{
enum direction{LEFT,DOWN,RIGHT,UP};

struct Piece
{
    int x;
    int y;
    Piece* next;
};

class Tetris
{
public:
    Tetris();
    ~Tetris();
    void ReturnDimensions(int* width, int* height);
private:
    const int width = 7;
    const int height = 14;
};

class Snake
{
public:
    Snake(int* CP)
    {
        continueplaying = CP;

        std::srand(std::time(0));

        Free = new bool*[width];
        for(int i=0;i<width;++i)
        {
            Free[i] = new bool[width];
            for(int k=0;k<width;++k)
                Free[i][k] = true;
        }
        Head = new Piece;
        Head->x = width/2;
        Head->y = Head->x;
        printf("%i,%i\n",Head->x,Head->y);
        Head->next = NULL;
        ToAdd = 4;
        MoveDir = RIGHT;

        Pickup.x = (1+std::rand())%Head->x + Head->x;
        Pickup.y = (1+std::rand())%Head->y + Head->y;

        Free[Head->x][Head->y]   = false;
        Free[Pickup.x][Pickup.y] = false;

        *continueplaying = 1;
    };
    ~Snake()
    {
        for(int i=0;i<width;++i)
            delete[] Free[i];
        delete[] Free;

        Piece* tempP = SecondLast();
        while(tempP != Head)
        {
            delete tempP->next;
            tempP->next = NULL;
            tempP = SecondLast();
        }
        delete tempP->next;
        delete Head;
    };

    void EmptyFunction();

    //True if Game over
    bool Move();

    void GoUp();
    void GoDown();
    void GoLeft();
    void GoRight();
    void Debug();

    bool** ReturnField();
    void* ReturnStuff(int a);

    void Reset();

private:
    Piece* SecondLast();
    //True if collision with self
    bool CheckCollision(int x, int y);
    void Collect();

    int width = 20;
    const int Value = 2;

    bool** Free;
    int* continueplaying;

    Piece* Head;
    int ToAdd;
    direction MoveDir;

    Piece Pickup;

    LTexture* Texture = NULL;
};
}

#endif
