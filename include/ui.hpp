#ifndef UI_H
#define UI_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "text.hpp"
#include <SDL/SDL_ttf.h>
using namespace std;

void loadPauseMenu(SDL_Surface *surface, GLuint *textureIdText);

#endif
