#include "geometry.hpp"

#include <iostream>



void fillGrid(){
//glPushMatrix();
  glScalef(1,-1,1.);
  glTranslatef(-1,-1,0);
  glScalef(0.1,0.1,1);
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      drawSquare(i,j);
    }
  }
  //glPopMatrix();
  SDL_GL_SwapBuffers();
}


void drawSquare(int i, int j){
  //std::cout << "ça fonctionne";
  glBegin(GL_QUADS);
    glColor3f(i*10,j*10,255);
      glVertex2f(i*h,j*w);
      glVertex2f(i*h,(j+2)*w);
      glVertex2f((i+2)*h,(j+2)*w);
      glVertex2f((i+2)*h,j*w);
  glEnd();
}
