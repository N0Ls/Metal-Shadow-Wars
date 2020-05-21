#ifndef PLAYER_H
#define PLAYER_H



#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "unit.hpp"

struct player {
  int id;
  char name[28];
  int nbUnits;
  int resources;
  unit units[255];
  bool isAlive;
  SDL_Color color;
} ;

void isAlive(player *playerToCheck);

void initPlayer(player *player, int id, int nbUnits, char name[], SDL_Color couleur);

void display_infos();
void buy_unit();

#endif
