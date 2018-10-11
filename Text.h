#ifndef TEXT_H
#define TEXT_H

#include <cstdio>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "IMG.h"

namespace Text
{

//Old
//bool Draw(SDL_Renderer* gRenderer,int x,int y,std::string Text,TTF_Font* Font,SDL_Color textColor = {255,255,255}, int width = 114);

class TextRenderer
{
public:
    TextRenderer(SDL_Renderer* renderer,std::string SmallText, std::string BoldText):Renderer(renderer)
    {
        TextureSmallText = new LTexture(Renderer);
        TextureBoldText = new LTexture(Renderer);

        std::string line = "images/"+SmallText+".png";
        if( !TextureSmallText->loadFromFile(line.c_str()) )
        {
            printf( "Failed to load small text texture!\n" );
        }
        line = "images/"+BoldText+".png";
        if( !TextureBoldText->loadFromFile(line.c_str()) )
        {
            printf( "Failed to load bold text texture!\n" );
        }
        if(!LoadMedia(SmallText,BoldText))
            printf("Failed to load text rects!\n");
    }
    ~TextRenderer()
    {
        Renderer = NULL;
    }
    void SetColor(bool small, Uint8 red, Uint8 green, Uint8 blue );
    //bool Draw(int x, int y, std::string Text,bool small = true, SDL_Color textColor = {255,255,255}, int width = 114);
    void Write(int x, int y, std::string Text, bool small);
    void Write(int x, int y, std::string Text, bool small, int width);
private:
    bool LoadMedia(std::string SmallTextPath, std::string BoldTextPath);

    SDL_Renderer* Renderer = NULL;
    LTexture* TextureSmallText = NULL;
    LTexture* TextureBoldText = NULL;
    SDL_Rect RectSmallText[95];
    SDL_Rect RectBoldText[95];
};
}
#endif
