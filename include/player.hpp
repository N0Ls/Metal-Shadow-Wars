#ifndef PLAYER_H
#define PLAYER_H

#include "unit.hpp"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

typedef struct {
  int id;
  char name[28];
  int nbUnits;
  int resources;
  unit units[255];
  bool isAlive;
} player;

bool isAlive(player *playerToCheck);

void initPlayer(player* player, int id, int nbUnits);

void display_infos();
void buy_unit();

#endif