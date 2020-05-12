#ifndef MAP_H
#define MAP_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

void fillGrid(GLuint textureIds[], GLuint textureLink[]);
Uint32 getpixel(SDL_Surface *surface, int x, int y);
void loadMap();
#endif
