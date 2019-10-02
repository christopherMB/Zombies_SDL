#include <stdlib.h>
#include "player_functions.hpp"

int player_order(int player, int** world)
{
    int choice = 0;

    switch(player)
    {
    case 1:
        choice = player1(world);
        break;
    case 2:
        choice = player2(world);
        break;
    case 3:
        choice = player3(world);
        break;
    case 4:
        choice = player4(world);
        break;
    case 5:
        choice = player5(world);
        break;
    }
return choice;
}


////////////////////////////////////////////////////////////////////////
///PLAYER CODE///
////////////////////////////////////////////////////////////////////////
int player1(int** world)
{
    return rand()%5;
}

int player2(int** world)
{
    return rand()%5;
}
int player3(int** world)
{
    return rand()%5;
}
int player4(int** world)
{
    return rand()%5;
}

int player5(int** world)
{
    return rand()%5;
}



