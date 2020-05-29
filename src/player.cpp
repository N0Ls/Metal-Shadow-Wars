#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "player.hpp"
#include "unit.hpp"
using namespace std;

/**
 *
 * Initialize Player's atttributes.
 *
 * @param player The player to initialize.
 * @param id The id of the player.
 * @param nbUnits The number of units that the player is gooing to get.
 * @param name The player name.
 * @param couleur The color of its units.
 *
 */
void initPlayer(player *player, int id, int nbUnits, char name[], SDL_Color couleur)
{
    player->id = id;
    strcpy(player->name, name);
    player->color = couleur;
    player->nbUnits = nbUnits;
    player->resources = 45;
    player->isAlive = true;
    std::cout << "Init Units" << '\n';

    //Initialization of the units
    for (int i = 0; i < nbUnits; i++)
    {
      Unit newUnit;
      initUnit(&newUnit, id, player,100, 50, 4, 3, i, 0);
      player->units.push_back(newUnit);
    }
    if(player->nbUnits >= 4){
      initRobot(&player->units.front());
      initDog(&player->units.back());
    }
}

/**
 *
 * Check if the player is alive or not.
 *
 * @param player The player to to check.
 *
 */
void isAlive(player *playerToCheck)
{
  if(playerToCheck->nbUnits <=0){
    playerToCheck->isAlive =false;
  }
}

/**
 *
 * Update the index number of the units of a player.
 *
 * @param player The player to to check.
 *
 */
void updateUnitIndex(player *player){
  for (int i = 0; i < player->units.size(); i++) {
    cout << player->units[i].arrayIndex<<endl;
    player->units[i].arrayIndex=i;
  }
}
