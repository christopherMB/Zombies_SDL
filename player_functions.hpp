#ifndef PLAYER_FUNCTIONS_HPP_INCLUDED
#define PLAYER_FUNCTIONS_HPP_INCLUDED

#include "params.hpp"

int player1(int** world);
int player2(int** world);
int player3(int** world);
int player4(int** world);
int player5(int** world);

///Main switch for player functions
int player_order(int player, int** world);
#endif // PLAYER_FUNCTIONS_HPP_INCLUDED
