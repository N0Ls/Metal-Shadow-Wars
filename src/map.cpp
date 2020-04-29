#include "map.hpp"
#include "constants.hpp"
using namespace std;
#include <iostream>
#include "texture.hpp"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


void drawQuads(){
  glBegin(GL_QUADS);
    glColor3f(1,1,1);
      glTexCoord2f( 0 , 0);
      glVertex2f(0,0);

      glTexCoord2f( 1 , 0);
      glVertex2f(MAP_TILE_SIZE,0);

      glTexCoord2f( 1 , 1);
      glVertex2f(MAP_TILE_SIZE,MAP_TILE_SIZE);

      glTexCoord2f( 0 , 1);
      glVertex2f(0,MAP_TILE_SIZE);
  glEnd();
}

void fillGrid(SDL_Surface* surface, GLuint textureIds[],GLuint textureLink[]){
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPushMatrix();
    glScalef(1,-1,1.);
    int t =0;
    for (int i = 0; i < MAP_SIZE; i++) {
      for (int y = 0; y < MAP_SIZE; y++) {
          glPushMatrix();
            glTranslatef((-GL_VIEW_SIZE/2)+i*MAP_TILE_SIZE,(-GL_VIEW_SIZE/2)+y*MAP_TILE_SIZE,0);
            glBindTexture(GL_TEXTURE_2D, textureIds[2]);
            drawQuads();

            if (textureLink[t] < 6){
              glBindTexture(GL_TEXTURE_2D, textureIds[textureLink[t]]);
            }
            else {
              glBindTexture(GL_TEXTURE_2D, textureIds[textureLink[2]]);
            }
            drawQuads();
          glPopMatrix();
          t++;
      }
    }

  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D, 0);





  SDL_GL_SwapBuffers();
}
