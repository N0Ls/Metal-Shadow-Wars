#ifndef TEXT_H
#define TEXT_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
using namespace std;

void createText(SDL_Surface *surfaceText, TTF_Font *police, GLuint *texture_id, char *txtContent, SDL_Color color);
void createTextureText(GLuint *texture, SDL_Surface *surfaceText);
void displayText(SDL_Surface *surfaceText,GLuint texture_id, float x, float y);

#endif
