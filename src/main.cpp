#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_rotozoom.h>

#include <iostream>
#include <sstream>


using namespace std;

int main( int argc, char **argv ) 
{
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "Failed to init SDL: %s\n", SDL_GetError() );
		return 4;
	}
	atexit(SDL_Quit);

    SDL_Surface* screen = SDL_SetVideoMode(1280, 720, 16, SDL_HWSURFACE|SDL_DOUBLEBUF/*|SDL_FULLSCREEN*/);

	bool done = false;
    while (!done)
    {
		SDL_Event event;
		if( SDL_PollEvent( &event ) )
		{
			if(event.type == SDL_QUIT)
			{
				done = true;
			}
		}
    }
} // main
