#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <stdio.h>

#include "functions.hpp"
#include "display.hpp"



int main ( int argc, char** argv )
{
    freopen("CON", "w", stdout);
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(WIDTH * GRAPHIC_WIDTH, HEIGHT * GRAPHIC_HEIGHT, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface** images_SDL = load_images();


    int players[NUMBER_OF_PLAYERS];

    int turns = 0;
    int winner = 0;

    int** world = create_world();
    init_world(world, players);




    // program main loop
    bool done = false;
    while (!done && player_left(players) != 0)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
            // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

            // check for keypresses
            case SDL_KEYDOWN:
            {
                // exit if ESCAPE is pressed
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    done = true;
                break;
            }
            }
        }
        spawn_zombies(world, players);//spawn zombies in corners

        move_players(world, players);//move each player according to their orders

        move_zombies(world, players);//move each zombie once

        print_world(world, screen, images_SDL);//display world
        if(LOG_WORLD){
            print_world_console(world);
        }

        if (winner == 0) winner = get_winner(players);

        SDL_Delay(WAIT_TIME);

        turns++;
    } // end main loop

    printf("PLAYER %d WINS in %d turns !\n", winner, turns);

    free_images(images_SDL);

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
