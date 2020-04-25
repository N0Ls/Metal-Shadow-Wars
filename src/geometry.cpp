#include "geometry.hpp"
#include "constants.hpp"
#include <iostream>


void drawQuads(){
  glBegin(GL_LINE_LOOP);
    glColor3f(0,0,1);
      glVertex2f(0,0);
      glVertex2f(MAP_TILE_SIZE,0);
      glVertex2f(MAP_TILE_SIZE,MAP_TILE_SIZE);
      glVertex2f(0,MAP_TILE_SIZE);
  glEnd();
}
void fillGrid(SDL_Surface* surface){
  glPushMatrix();
    glScalef(1,-1,1.);
    for (int i = 0; i < MAP_SIZE; i++) {
      for (int y = 0; y < MAP_SIZE; y++) {
        glPushMatrix();
          glTranslatef((-GL_VIEW_SIZE/2)+i*MAP_TILE_SIZE,(-GL_VIEW_SIZE/2)+y*MAP_TILE_SIZE,0);
          drawQuads();
        glPopMatrix();
      }
    }

  glPopMatrix();


  SDL_GL_SwapBuffers();
}
