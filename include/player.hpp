#ifndef PLAYER_H
#define PLAYER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include "unit.hpp"
using namespace std;


//Declaring the structure
struct player {
  int id;
  char name[28];
  int nbUnits;
  int resources;
  vector <Unit> units;
  bool isAlive;
  SDL_Color color;
} ;

//Declaration of prototypes of functions related to players
void isAlive(player *playerToCheck);
void initPlayer(player *player, int id, int nbUnits, const char name[], SDL_Color couleur);
void updateUnitIndex(player *player);

//Not implemented yet
void buy_unit();

#endif
