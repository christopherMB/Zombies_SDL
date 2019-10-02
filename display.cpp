#include "display.hpp"
#include <string.h>


void print_world(int** world, SDL_Surface* screen, SDL_Surface** images){

        SDL_Rect dstrect;
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        for (int i = 0; i < HEIGHT; i++){
            for (int j = 0; j< WIDTH; j++){
                if (world[i][j] != 0 && world[i][j] != ZOMBIE){
                    dstrect.x = j * GRAPHIC_WIDTH;
                    dstrect.y = i * GRAPHIC_HEIGHT;
                    SDL_BlitSurface(images[world[i][j]], 0, screen, &dstrect);
                }
                else if(world[i][j] == ZOMBIE){
                    dstrect.x = j * GRAPHIC_WIDTH;
                    dstrect.y = i * GRAPHIC_HEIGHT;
                    SDL_BlitSurface(images[0], 0, screen, &dstrect);
                }
            }
        }
        SDL_Flip(screen);
}


SDL_Surface** load_images(){
    SDL_Surface** images = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * NUMBER_OF_PLAYERS + 1);

    // load images
    images[0] = SDL_LoadBMP("images/z.bmp");

    for (int i = 1; i <= NUMBER_OF_PLAYERS; i++){
        char p_number[5];
        sprintf(p_number, "%d", i);
        char j[20] = "images/j";
        strcat(j,p_number);
        strcat(j, ".bmp");
        images[i] = SDL_LoadBMP(j);

    }
    return images;
}

void free_images(SDL_Surface ** images){
    for (int i = 0; i <= NUMBER_OF_PLAYERS; i++){
        SDL_FreeSurface(images[i]);
    }
    free(images);
}
