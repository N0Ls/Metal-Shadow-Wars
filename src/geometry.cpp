#include "geometry.hpp"

#include <iostream>



void fillGrid(){
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      drawSquare(i,j);
    }
  }
}
void drawSquare(int i, int j){
  glBegin(GL_QUADS);
    glColor3f(1/(i+1),1/(j+1),1/(i + j + 1));
      glVertex2f(i*h,j*w);
      glVertex2f(i*h,(j+2)*w);
      glVertex2f((i+2)*h,(j+2)*w);
      glVertex2f((i+2)*h,j*w);
  glEnd();
}
