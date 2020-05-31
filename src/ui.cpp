#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "ui.hpp"
#include "text.hpp"
#include "constants.hpp"
#include "player.hpp"
using namespace std;


/**
 *
 * Basic quad drawing for menus
 *
 *
 */
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


/**
 *
 * Load the pause menu content .
 *
 * @param surface The surface used to create the texture.
 * @param textureIdText The texture container.
 *
 */
void loadPauseMenu(SDL_Surface *surface, GLuint *textureIdText){
  TTF_Init();
  TTF_Font *font =TTF_OpenFont("./assets/fonts/indelible.ttf", 40);
  SDL_Color couleurTXT = {0,0, 255};

  char pauseMenuText[25] = "Pause";
  createText(surface,font, textureIdText, pauseMenuText, couleurTXT);
  TTF_CloseFont(font);
}

/**
 *
 * Displays the pause menu.
 *
 * @param surface The surface used for display.
 * @param textureIdText The texture container.
 *
 */
void displayPauseMenu(SDL_Surface *surface, GLuint *textureIdText){
  glColor4f(0,0,0,0.5);
  glPushMatrix();
    glTranslatef(-50,-50,0);
    glScalef(25,25,0);
    drawQuadsMenu();
  glPopMatrix();
  displayText(surface,*textureIdText, 0, -40);
}

/**
 *
 * Load the end screen content .
 *
 * @param surface The surface used to create the texture.
 * @param textureIdText The texture container.
 * @param winner The winner player.
 *
 */
void loadEndMenu(SDL_Surface *surface, GLuint *textureIdText, player *winner){
  TTF_Init();
  TTF_Font *font =TTF_OpenFont("./assets/fonts/indelible.ttf", 40);
  SDL_Color couleurTXT = {255,255, 255};

  char congrats[25] = "CONGRATULATIONS";
  createText(&surface[0],font, &textureIdText[0], congrats, couleurTXT);

  TTF_Font *font2 =TTF_OpenFont("./assets/fonts/ChelseaMarket-Regular.ttf", 40);


  createText(&surface[1],font2, &textureIdText[1], winner->name, couleurTXT);

  TTF_CloseFont(font);
  TTF_CloseFont(font2);


}

/**
 *
 * Displays the pause menu.
 *
 * @param surface The surface used for display.
 * @param textureIdText The texture container.
 *
 */
void displayEndMenu(SDL_Surface *surface, GLuint *textureIdText){
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glColor4f(0,0,0,0.5);
  glPushMatrix();
    glTranslatef(-50,-50,0);
    glScalef(25,25,0);
    drawQuadsMenu();
  glPopMatrix();
  displayText(&surface[0],textureIdText[0], 0, -10);
  displayText(&surface[1],textureIdText[1], 0, 10);
  SDL_GL_SwapBuffers();
}
