#ifndef UI_H
#define UI_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "text.hpp"
#include "player.hpp"
#include <SDL/SDL_ttf.h>
using namespace std;

//Declaration of prototypes
void loadPauseMenu(SDL_Surface *surface, GLuint *textureIdText);
void displayPauseMenu(SDL_Surface *surface, GLuint *textureIdText);
void loadEndMenu(SDL_Surface *surface, GLuint *textureIdText, player *winner);
void displayEndMenu(SDL_Surface *surface, GLuint *textureIdText);

//ENUM NOT USED WIP
enum UI_End_Menu {
  FELICITATION = 0,
  WINNER
};


#endif
