#ifndef LYONSSDL_HPP
#define LYONSSDL_HPP
#include <SDL/SDL.h>
#include <string>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <vector>
#include <fstream>

using namespace std;

bool init(SDL_Surface *screen, int width, int height, std::string message);
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
void apply_surface(int srcx, int srcy, int srcw, int srch, int x, int y, SDL_Surface* source, SDL_Surface* destination);
SDL_Surface *load_image( std::string filename );
SDL_Surface *load_image( std::string filename , bool optimize);
SDL_Surface *scale_load_image( std::string filename, int x, int y);

#endif // LYONSSDL_HPP
