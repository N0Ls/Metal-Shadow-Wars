#ifndef MAP_H
#define MAP_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "constants.hpp"

//Structure
struct TileMap{
  GLuint textureId;
  bool isWalkable;
  bool isDestructible;
};

//Declaration of prototypes
void setTile(TileMap *tile, GLuint textureId, bool isWalkable, bool isDestructible);
void fillGrid(GLuint textureIds[], GLuint textureLink[], TileMap *tabMapTile);
Uint32 getpixel(SDL_Surface *surface, int x, int y);
void loadMap(TileMap *tabMapTile);
void destroyEnvironnement(TileMap *tabMapTile, int x , int y);
#endif
