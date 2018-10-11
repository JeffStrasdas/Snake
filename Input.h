#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <cstdio>

#include "Game.h"


const int MK = 231; //Should be enough

namespace Input
{
typedef void (*Keyfunction) ();
typedef void (Game::Snake::*Funktion)();


void EmptyFunc();

class InputHandler
{
public:
    InputHandler(Game::Snake* snek,int* CP);
    ~InputHandler(){};

    void Update();
    void AssignKey(SDL_Scancode KeyFkt, void (*Function)());
    void AssignKey(SDL_Scancode KeyFkt, void (Game::Snake::*Function)());

private:
    SDL_Event e;
    Keyfunction KeyFkt[MK] = {NULL};
    Funktion Test[MK] = {NULL};
    Game::Snake* S;


    int* ContinuePlaying;
};

}

#endif
