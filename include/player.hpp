#ifndef PLAYER_H
#define PLAYER_H



#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "unit.hpp"
#include <vector>
using namespace std;

struct player {
  int id;
  char name[28];
  int nbUnits;
  int resources;
  vector <Unit> units;
  bool isAlive;
  SDL_Color color;
} ;

void isAlive(player *playerToCheck);

void initPlayer(player *player, int id, int nbUnits, char name[], SDL_Color couleur);
void updateUnitIndex(player *player);

void display_infos();
void buy_unit();

#endif
