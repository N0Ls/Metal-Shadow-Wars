#include <SDL/SDL_ttf.h>
#include <iostream>
#include "text.hpp"
using namespace std;


/**
 *
 * Create a text.
 *
 * @param surfaceText The surface used to create the text.
 * @param font The font used for this text.
 * @param texture_id The texture storer.
 * @param txtContent The text content itself.
 * @param color The color of the text.
 *
 */
void createText(SDL_Surface *surfaceText, TTF_Font *police, GLuint *texture_id, char *txtContent, SDL_Color color){
  SDL_Surface* sText = TTF_RenderUTF8_Blended(police, txtContent, color);
  if(sText == NULL){
    printf("Can't load text");
    exit(EXIT_FAILURE);
  }
  createTextureText(texture_id,sText);
  surfaceText->w = sText->w;
  surfaceText->h = sText->h;
  SDL_FreeSurface(sText);
}


/**
 *
 * Create a texture for surface.
 *
 * @param texture The texture container.
 * @param surfaceText The surface used to create the texture.
 *
 */
void createTextureText(GLuint *texture, SDL_Surface *surfaceText){
  if(surfaceText==NULL){
    exit(1);
  }
  glGenTextures(1,texture);
  glBindTexture(GL_TEXTURE_2D,*texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  GLenum format;
  switch(surfaceText->format->BytesPerPixel){
    case 1:
          format = GL_RED;
          break;
      case 3:
          format = GL_RGB;
          break;
      case 4:
          format = GL_RGBA;
          break;
      default:
          fprintf(stderr, "Format des pixels de l'image non supporte.\n");
          exit(EXIT_FAILURE);
  }
  glTexImage2D(GL_TEXTURE_2D,0,format,surfaceText->w,surfaceText->h,0,format,GL_UNSIGNED_BYTE, surfaceText->pixels);
  glBindTexture(GL_TEXTURE_2D,0);
}


/**
 *
 * Create a texture for surface.
 *
 * @param texture The texture container.
 * @param surfaceText The surface used to create the texture.
 *
 */
void displayText(SDL_Surface *surfaceText, GLuint texture_id, float x, float y){
  float w = (float)surfaceText->w/10;
  float h = (float)surfaceText->h/10;
  glLoadIdentity();
  glClearColor(0, 0, 0, 0);
  glColor3f(1,1,1);
  glPushMatrix();
    glScalef(1,-1,1);
    glTranslatef(-w/2,-h/2,0);
    //glTranslatef(-50,-50,0);
    glTranslatef(x,y,0);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glBegin(GL_QUADS);

    glTexCoord2f(1,1);
    glVertex2f(w,h);

    glTexCoord2f(0,1);
    glVertex2f(0,h);

    glTexCoord2f(0,0);
    glVertex2f(0,0);

    glTexCoord2f(1,0);
    glVertex2f(w,0);

    glEnd();
    glBindTexture(GL_TEXTURE_2D,0);

  glPopMatrix();
}
