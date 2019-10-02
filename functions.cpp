#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#include "functions.hpp"
#include <time.h>
#include <stdio.h>

int** create_world()
{
    int** world = (int**)malloc(sizeof(int*) * HEIGHT);

    for(int i = 0; i < HEIGHT ; i++)
    {
        world[i] = (int*)malloc(sizeof(int) * WIDTH);
        for (int j = 0; j < WIDTH; j++)
        {
            world[i][j] = 0;
        }
    }
    return world;
}

int** copy_world(int** origin)
{
    int** world = (int**)malloc(sizeof(int*) * HEIGHT);

    for(int i = 0; i < HEIGHT ; i++)
    {
        world[i] = (int*)malloc(sizeof(int) * WIDTH);
        for (int j = 0; j < WIDTH; j++)
        {
            world[i][j] = origin[i][j];
        }
    }
    return world;
}



void free_world(int** world)
{
    for(int i = 0; i < HEIGHT; i++)
    {
        free(world[i]);
    }
    free(world);
}

int move_zomb_to(int i, int j, int** world, int players[NUMBER_OF_PLAYERS])
{
    if (i >= 0 && i < HEIGHT && j >= 0 && j <= WIDTH )
    {
        if (world[i][j] > 0 && world[i][j] <= NUMBER_OF_PLAYERS)
        {
            players[world[i][j] - 1] = 0;
            if(LOG){
                printf("PLAYER %d HAS DIED !\n", world[i][j]);
            }
            world[i][j] = ZOMBIE;
            return 1;
        }
        else if(world[i][j] == 0)
        {
            world[i][j] = ZOMBIE;
            return 1;
        }

    }
    return 0;

}

void spawn_zombies(int** world, int players[NUMBER_OF_PLAYERS])
{
    int doom = rand()%4;
    if(doom == 0)
    {
        move_zomb_to(0,0, world, players);
    }
    doom = rand()%4;
    if(doom == 0)
    {
        move_zomb_to(HEIGHT - 1,WIDTH - 1, world, players);
    }
    doom = rand()%4;
    if(doom == 0)
    {
        move_zomb_to(0,WIDTH - 1, world, players);
    }
    doom = rand()%4;
    if(doom == 0)
    {
        move_zomb_to(HEIGHT - 1,0, world, players);
    }
}

void init_world(int** world, int players[NUMBER_OF_PLAYERS])
{
    srand(time(NULL));
    for (int i = 1; i <= NUMBER_OF_PLAYERS; i++)
    {
        players[i - 1] = 1;
        world[HEIGHT/2][(WIDTH/2) - NUMBER_OF_PLAYERS +(i)] = i;
    }
}

Zombie* create_zomb(int i, int j)
{
    Zombie* temp = (Zombie*)malloc(sizeof(Zombie));
    temp->i = i;
    temp->j = j;
    temp->next = NULL;
    return temp;
}

void add_zomb(Zombie** zombs, Zombie* new_zomb)
{
    new_zomb->next = *zombs;
    *zombs = new_zomb;
}

void free_zomb(Zombie* zombs)
{
    if(zombs)
    {
        free_zomb(zombs->next);
        free(zombs);
    }
}

void move_zombies(int** world, int players[NUMBER_OF_PLAYERS])
{
    Zombie* zombs = NULL;
    for(int i = 0; i < HEIGHT ; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if(world[i][j] == ZOMBIE)
                add_zomb(&zombs, create_zomb(i,j));
        }
    }

    Zombie* temp = zombs;
    while(temp != NULL)
    {
        move_zombie(temp, world, players);
        temp = temp->next;
    }
    free_zomb(zombs);
}

void move_zombie(Zombie* temp, int** world, int players[NUMBER_OF_PLAYERS])
{
    int direct = rand()%4 + 1;
    int moved = 0;
    switch(direct)
    {
    case BAS :
        moved = move_zomb_to(temp->i + 1, temp->j, world, players);
        break;
    case HAUT :
        moved = move_zomb_to(temp->i - 1, temp->j, world, players);
        break;
    case DROITE :
        moved = move_zomb_to(temp->i, temp->j + 1, world, players);
        break;
    case GAUCHE :
        moved = move_zomb_to(temp->i, temp->j - 1, world, players);
        break;
    }

    if (moved)
    {
        world[temp->i][temp->j] = 0;
    }
}

int player_left(int players[NUMBER_OF_PLAYERS])
{
    int check = 0;
    for(int i = 0; i < NUMBER_OF_PLAYERS ; i++)
    {
        check += players[i];
    }
    return check;
}

int get_winner(int players[NUMBER_OF_PLAYERS]){
    if (player_left(players) == 1){
        int winner = 0;
        for (int i = 0; i < NUMBER_OF_PLAYERS; i++){
            if (players[i] == 1){
                winner = i + 1;
            }
        }
        return winner;
    }
    return 0;
}

int move_player_to(int play, int i, int j, int** world)
{
    if (i >= 0 && i < HEIGHT && j >= 0 && j < WIDTH )
    {
        if(world[i][j] == 0)
        {
            world[i][j] = play;
            return 1;
        }

    }
    return 0;

}


void move_players(int** world, int players[NUMBER_OF_PLAYERS])
{
    for(int i = 1 ; i <= NUMBER_OF_PLAYERS; i++)
    {
        int moved = 0;

        if (players[i - 1] == 1)
        {
            int** world_cop = copy_world(world);
            int direct = player_order(i, world_cop);
            free_world(world_cop);

            //Get player position
            int posi = 0;
            int posj = 0;
            if (direct != 0)
            {
                for(int a = 0; a < HEIGHT ; a++){
                    for(int b = 0; b < WIDTH; b++){
                        if (world[a][b] == i){
                            posi = a;
                            posj = b;
                        }
                    }
                }
            }


            //ask for direction
            switch(direct)
            {
            case BAS :
                moved = move_player_to(i, posi + 1, posj, world);
                break;
            case HAUT :
                moved = move_player_to(i, posi - 1, posj, world);
                break;
            case DROITE :
                moved = move_player_to(i, posi, posj + 1, world);
                break;
            case GAUCHE :
                moved = move_player_to(i, posi, posj - 1, world);
                break;
            }
            if (moved)
            {
                world[posi][posj] = 0;
            }
        }


    }

}
