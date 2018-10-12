#include "Window.h"
#include "Input.h"
#include "Game.h"



int main( int argc, char* args[] )
{
    int* play = new int;
    *play = 1;

    Game::Snake* Game = new Game::Snake(play);
    Input::InputHandler* InputHandler = new Input::InputHandler(Game,(int*)Game->ReturnStuff(3));
    Window::Container* Win = new Window::Container(Game->ReturnField(),(int*)Game->ReturnStuff(0),(int*)Game->ReturnStuff(1),(int*)Game->ReturnStuff(2),(int*)Game->ReturnStuff(3));

    InputHandler->AssignKey(SDL_SCANCODE_A,&Game->GoLeft);
    InputHandler->AssignKey(SDL_SCANCODE_S,&Game->GoDown);
    InputHandler->AssignKey(SDL_SCANCODE_D,&Game->GoRight);
    InputHandler->AssignKey(SDL_SCANCODE_W,&Game->GoUp);
    InputHandler->AssignKey(SDL_SCANCODE_LEFT,&Game->GoLeft);
    InputHandler->AssignKey(SDL_SCANCODE_DOWN,&Game->GoDown);
    InputHandler->AssignKey(SDL_SCANCODE_RIGHT,&Game->GoRight);
    InputHandler->AssignKey(SDL_SCANCODE_UP,&Game->GoUp);
    InputHandler->AssignKey(SDL_SCANCODE_SPACE,&Game->Debug);

    while(true)
    {
        //if(*play == 1)
            *play = Game->Move();
        InputHandler->Update();
        Win->Update(100);

        //if(*play == 0)
            //Game->Reset();
    }
    return 0;
}
