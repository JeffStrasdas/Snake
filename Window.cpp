#include "Window.h"

void Rainbow(int number, int* c)
{
    number %= 255*6;
    switch(number/255)
    {
    case 0:
        c[0] = 255;
        c[1] = number%255;
        c[2] = 0;
        break;
    case 1:
        c[0] = 255-number%255;
        c[1] = 255;
        c[2] = 0;
        break;
    case 2:
        c[0] = 0;
        c[1] = 255;
        c[2] = number%255;
        break;
    case 3:
        c[0] = 0;
        c[1] = 255 - number%255;
        c[2] = 255;
        break;
    case 4:
        c[0] = number%255;
        c[1] = 0;
        c[2] = 255;
        break;
    case 5:
        c[0] = 255;
        c[1] = 0;
        c[2] = 255 - number%255;
        break;
    default:
        printf("dunno\n");
        break;
    }

}


bool Window::Container::Init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		Window = SDL_CreateWindow( "snek", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( Window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			Renderer = SDL_CreateRenderer( Window, -1, SDL_RENDERER_ACCELERATED );
			if( Renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer

				SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
					success = false;
				}

				//Initialise SDL_ttf
				if(TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n",TTF_GetError());
                    success = false;
                }
			}
		}
	}

	return success;
}

bool Window::Container::Update(int delay)
{
    SDL_RenderClear(Renderer);
    //Snake
    Rainbow(number,c);
    number += 11;
    Visual->setColor(c[0],c[1],c[2]);
    for(_x=0;_x<width;++_x)
        for(_y=0;_y<width;++_y)
            if(!Field[_x][_y])
                Visual->render(_x*tilewidth+tilebuffer,_y*tilewidth+tilebuffer);
    //Pickup
    Visual->setColor(255,0,0);
    Visual->render(*x *tilewidth+tilebuffer,*y *tilewidth+tilebuffer);
    //Text
    if(*continueplaying == 0)
        TextRenderer->Write(0,0,"GAME OVER",true);

    //i += delay;
    //Rainbow(i,colors);
    //TextRenderer->SetColor(true,colors[0],colors[1],colors[2]);
    //if(y+7 > SCREEN_HEIGHT || y < 0)
    //    ay = -ay;
    //if(x+60 > SCREEN_WIDTH || x < 0)
    //    ax = -ax;
    //x += ax;
    //y += ay;
    //TextRenderer->Write(x,y,"testing text",true);
    SDL_RenderPresent( Renderer );
    SDL_Delay(delay);
    return true;
}
