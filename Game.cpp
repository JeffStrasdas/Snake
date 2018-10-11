#include "Game.h"

void Game::Snake::EmptyFunction(){};

Game::Piece* Game::Snake::SecondLast()
{
    Piece* tempP = Head;
    if(tempP->next == NULL)
        return tempP;
    while(tempP->next->next != NULL)
        tempP = tempP->next;
    return tempP;
}

bool Game::Snake::Move()
{
    int new_x;// = Head->x + MoveDir == LEFT ? -1 : MoveDir == RIGHT ? 1 : 0;
    int new_y;// = Head->y + MoveDir == UP   ? -1 : MoveDir == DOWN  ? 1 : 0;
    if(MoveDir == LEFT)
    {
        new_x = -1;
        new_y = 0;
    }
    else if(MoveDir == RIGHT)
    {
        new_x = 1;
        new_y = 0;
    }
    else if(MoveDir == UP)
    {
        new_x = 0;
        new_y = -1;
    }
    else
    {
        new_x = 0;
        new_y = 1;
    }

    new_x += Head->x;
    new_y += Head->y;

    if(CheckCollision(new_x,new_y))
    {
        continueplaying = 0;
        return false;
    }
    Piece* tempP = new Piece;
    tempP->x = new_x;
    tempP->y = new_y;
    tempP->next = Head;
    Head = tempP;

    Free[new_x][new_y] = false;

    if(ToAdd > 0 )
    {
        printf("%i\n",ToAdd);
        --ToAdd;
        return true;
    }

    tempP = SecondLast();
    Free[tempP->next->x][tempP->next->y] = true;
    delete tempP->next;
    tempP->next = NULL;

    return true;
}

void Game::Snake::GoUp(){if(MoveDir != DOWN) MoveDir = UP;}
void Game::Snake::GoDown(){if(MoveDir != UP) MoveDir = DOWN;}
void Game::Snake::GoLeft(){if(MoveDir != RIGHT) MoveDir = LEFT;}
void Game::Snake::GoRight(){if(MoveDir != LEFT) MoveDir = RIGHT;}
void Game::Snake::Debug()
{
    int z = 0;
    Game::Piece* tempP = Head;
    while(tempP != NULL)
    {
        z++;
        tempP = tempP->next;
    }
    printf("\nLength: %i, Maximal length: %i\ncurrent position: %i,%i\n",z,z+ToAdd,Head->x,Head->y);
}

void Game::Snake::Collect()
{
    ToAdd += Value;
}

bool Game::Snake::CheckCollision(int x, int y)
{
    if(x < 0 || x >= width || y < 0 || y >= width)
        return true;
    if(!Free[x][y])
    {
        if(Pickup.x == x && Pickup.y == y)
        {
            ToAdd += 3;
            while(!Free[Pickup.x][Pickup.y])
            {
                Pickup.x = rand()%width;
                Pickup.y = rand()%width;
            }
            Free[Pickup.x][Pickup.y] = false;
            return false;
        }
        else
            return true;
    }
    return false;
}

bool** Game::Snake::ReturnField()
{
    return Free;
}

void* Game::Snake::ReturnStuff(int a)
{
    switch(a)
    {
    case 0:
        return &Pickup.x;
    case 1:
        return &Pickup.y;
    case 2:
        return &width;
    case 3:
        return &continueplaying;
    }
}

void Game::Snake::Reset()
{
    Game::Piece* tempP = SecondLast();
    while(tempP != Head)
    {
        delete tempP->next;
        tempP->next = NULL;
        tempP = SecondLast();
    }
    delete Head->next;
    Head->next = NULL;


    Head->x = width/2;
    Head->y = width/2;
    MoveDir = RIGHT;
    ToAdd = 4;

    //Something breaks here
    *continueplaying = 1;
    printf("das");

    for(int i=0;i<width;++i)
    {
        for(int k=0;k<width;++k)
            Free[i][k] = true;
    }

    Pickup.x = (1+std::rand())%Head->x + Head->x;
    Pickup.y = (1+std::rand())%Head->y + Head->y;

    Free[Head->x][Head->y]   = false;
    Free[Pickup.x][Pickup.y] = false;

    printf("Reset\n");
}

