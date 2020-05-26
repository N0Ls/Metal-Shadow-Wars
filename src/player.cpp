using namespace std;
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "player.hpp"
#include "unit.hpp"

void initPlayer(player *player, int id, int nbUnits, char name[], SDL_Color couleur)
{
    player->id = id;
    strcpy(player->name, name);
    player->color = couleur;
    player->nbUnits = nbUnits;
    player->resources = 45;
    player->isAlive = true;
    std::cout << "Init Units" << '\n';
    for (int i = 0; i < nbUnits; i++)
    {
      Unit newUnit;
      initUnit(&newUnit, i, player,100, 50, 4, 3, i, 0);
      player->units.push_back(newUnit);

        // setCoordinates(player->units + i, rand()%9, rand()%9);
        // updateDisplayCoordinates(player->units + i);
    }
}

void isAlive(player *playerToCheck)
{
  if(playerToCheck->nbUnits <=0){
    playerToCheck->isAlive =false;
  }
}
