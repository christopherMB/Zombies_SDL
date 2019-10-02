#ifndef FUNCTIONS_HPP_INCLUDED
#define FUNCTIONS_HPP_INCLUDED

#include "params.hpp"
#include "player_functions.hpp"

typedef struct Zombie{
    int i;
    int j;
    struct Zombie* next;
}Zombie;

///World processing functions
int** create_world();
void init_world(int** world, int players[NUMBER_OF_PLAYERS]);
int** copy_world(int** origin);
void free_world(int** world);

///Players and winners
int player_left(int players[NUMBER_OF_PLAYERS]);
int get_winner(int players[NUMBER_OF_PLAYERS]);
void move_players(int** world, int players[NUMBER_OF_PLAYERS]);

///Zombies
int move_zomb_to(int i, int j, int** world, int players[NUMBER_OF_PLAYERS]);
void spawn_zombies(int** world, int players[NUMBER_OF_PLAYERS]);
Zombie* create_zomb(int i, int j);
void add_zomb(Zombie** zombs, Zombie* new_zomb);
void free_zomb(Zombie* zombs);
void move_zombies(int** world, int players[NUMBER_OF_PLAYERS]);
void move_zombie(Zombie* temp, int** world, int players[NUMBER_OF_PLAYERS]);




#endif // FUNCTIONS_HPP_INCLUDED
