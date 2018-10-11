#include "Input.h"
#include "Game.h"


void Input::EmptyFunc(){}

void Input::InputHandler::Update()
{
    while( SDL_PollEvent( &e ) != 0 )
    {
        //User requests quit
        if( e.type == SDL_QUIT )
        {
            return;
        }
        //Handle keyboard input
        if(e.type == SDL_KEYDOWN)
        {
            //KeyFkt[e.key.keysym.scancode]();
            (S->*Test[e.key.keysym.scancode])();
        }
    }
}

void Input::InputHandler::AssignKey(SDL_Scancode Key, void (*Function)())
{
    KeyFkt[Key] = Function;
}
void Input::InputHandler::AssignKey(SDL_Scancode Key, void (Game::Snake::*Function)())
{
    Test[Key] = Function;
}

Input::InputHandler::InputHandler(Game::Snake* snek,int* CP)
{
    S = snek;
    for(int i=0;i<MK;++i)
        Test[i] = &S->EmptyFunction; //KeyFkt[i] = &EmptyFunc;

    ContinuePlaying = CP;
};
