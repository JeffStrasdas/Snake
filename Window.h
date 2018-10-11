#ifndef WINDOW_H
#define WINDOW_H

#include "Text.h"
#include "Input.h"

namespace Window
{
//Object on the window
struct Object
{
    int ID;
    int x,y;
    SDL_Rect* clip    = NULL;
    LTexture* texture = NULL;
    Object* next      = NULL;
};

class ProperWindow
{
public:
    ProperWindow();
    ~ProperWindow();

    Object* AddObject(int ID,int x,int y,SDL_Rect* clip, LTexture* texture)
    {
        //check if there are any objects
        if(LocalObject == NULL)
        {
            LocalObject = new Object;
            LocalObject->ID = ID;
            LocalObject->x = x;
            LocalObject->y = y;
            LocalObject->clip = clip;
            LocalObject->texture = texture;
            return LocalObject;
        }
        //Get to the last object
        Object* tempO = LocalObject;
        while(tempO != NULL)
            tempO = tempO->next;
        tempO->next = new Object;
        tempO = tempO->next;
        tempO->ID = ID;
        tempO->x = x;
        tempO->y = y;
        tempO->clip = clip;
        tempO->texture = texture;
        return tempO;
    }
    RemoveObject(int ID);

    typedef bool (*test)();
    void Check(test ToCheck);

    RenderScene();

private:
    int screen_width,screen_height;

    Object* LocalObject = NULL;

    SDL_Renderer* Renderer;
    SDL_Window*   Window;
    LTexture* Visual;


    Text::TextRenderer* TextRenderer;
};

class Container
{
public:
    Container(bool** newField,int* sx, int* sy,int* w,int* CP)
    {
        Field = newField;
        x = sx;
        y = sy;
        width = *w;
        continueplaying = CP;
        number = 0;
        tilewidth = SCREEN_WIDTH/width;
        tilebuffer = tilewidth/12;
        Renderer = NULL;
        Window   = NULL;

        Init();
        TextRenderer = new Text::TextRenderer(Renderer,"SmallText","SmallText");
        TextRenderer->SetColor(true,0,0,0);

        Visual = new LTexture(Renderer);
        Visual->createTexture({255,255,255,255},tilewidth-tilebuffer,tilewidth-tilebuffer,Window);
    };
    ~Container()
    {
        ///TODO: proper closing method
        //deleting renderer and window?
        delete TextRenderer;
        //close();
    };

    bool Update(int delay);


private:
    bool Init();

    bool** Field;

    int tilewidth, tilebuffer;
    int _x,_y,width;
    int* x;
    int* y;
    int* continueplaying;

    int number;
    int c[3] = {0,0,0};

    SDL_Renderer* Renderer;
    SDL_Window*   Window;
    LTexture* Visual;


    Text::TextRenderer* TextRenderer;
};
}
#endif

