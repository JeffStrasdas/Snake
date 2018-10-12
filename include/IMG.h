#ifndef IMG_H
#define IMG_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

const float scaling_factor = 1.0;
//Screen dimension constants
const int SCREEN_WIDTH  = 600 * scaling_factor;
const int SCREEN_HEIGHT = 600 * scaling_factor;

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture(SDL_Renderer* Renderer);

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path);

		//Creates image from font string
        bool loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font* gFont );

        //Creates texture with secified width and height
        bool createTexture(SDL_Color color, int w,int h,SDL_Window* gWindow);

		//Deallocates texture
		void free();

		//Renders texture at given point
		void render( int x, int y , SDL_Rect* clip = NULL );

        //Renders texture at given point including angle
        void renderx(int x , int y , SDL_Rect* clip = NULL , double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

		//Sets color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Gets image dimensions
		int getWidth();
		int getHeight();

		 //Pixel manipulators
		 bool lockTexture();
		 bool unlockTexture();
		 void* getPixels();
		 int getPitch();

	private:
	    //The used Renderer
	    SDL_Renderer* gRenderer;

		//The actual hardware texture
		SDL_Texture* mTexture;
        void* mPixels;
		int mPitch;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//Starts up SDL and creates window
bool init(SDL_Window* gWindow);

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();


#endif
