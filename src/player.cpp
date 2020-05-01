using namespace std;
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "player.hpp"
#include "unit.hpp"

void initPlayer(player *player, int id, int nbUnits)
{
    player->id = id;
    //strcpy(player->name, name);
    player->nbUnits = nbUnits;
    player->resources = 45;
    player->isAlive = true;

    for (int i = 0; i < nbUnits; i++)
    {
        initUnit(player->units + i, i, 100, 50, 7, 3, i, 0);
        setCoordinates(player->units + i, rand()%9, rand()%9);
    }
}

/*bool isAlive(player *playerToCheck)
{
    int n = 0;
    unit u;
    while (u != nullptr)
    {
        n++;
        u = playerToCheck->units[n];
    }
    if (n > 0)
        return true;
    else
        return false;
}*/
