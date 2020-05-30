#include "ui.hpp"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "text.hpp"
#include <SDL/SDL_ttf.h>
using namespace std;

void loadPauseMenu(SDL_Surface *surface, GLuint *textureIdText){
  TTF_Init();
  TTF_Font *font =TTF_OpenFont("./fonts/indelible.ttf", 40);
  SDL_Color couleurTXT = {0,0, 255};

  char pauseMenuText[25] = "Pause";
  createText(surface,font, textureIdText, pauseMenuText, couleurTXT);
  TTF_CloseFont(font);
}
