#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include "params.hpp"
#include <SDL/SDL.h>



void print_world(int** world, SDL_Surface* screen, SDL_Surface** images);

SDL_Surface** load_images();
void free_images(SDL_Surface ** images);

#endif // DISPLAY_H_INCLUDED
