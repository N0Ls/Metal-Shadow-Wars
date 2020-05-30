#include "ui.hpp"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "text.hpp"
#include <SDL/SDL_ttf.h>
#include "constants.hpp"
using namespace std;

void drawQuadsMenu()
{
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex2f(0, 0);

  glTexCoord2f(1, 0);
  glVertex2f(MAP_TILE_SIZE, 0);

  glTexCoord2f(1, 1);
  glVertex2f(MAP_TILE_SIZE, MAP_TILE_SIZE);

  glTexCoord2f(0, 1);
  glVertex2f(0, MAP_TILE_SIZE);
  glEnd();
}

void loadPauseMenu(SDL_Surface *surface, GLuint *textureIdText){
  TTF_Init();
  TTF_Font *font =TTF_OpenFont("./fonts/indelible.ttf", 40);
  SDL_Color couleurTXT = {0,0, 255};

  char pauseMenuText[25] = "Pause";
  createText(surface,font, textureIdText, pauseMenuText, couleurTXT);
  TTF_CloseFont(font);
}

void displayPauseMenu(SDL_Surface *surface, GLuint *textureIdText){
  glColor4f(0,0,0,0.5);
  glPushMatrix();
    glTranslatef(-50,-50,0);
    glScalef(25,25,0);
    drawQuadsMenu();
  glPopMatrix();
  displayText(surface,*textureIdText, 0, -40);
}
