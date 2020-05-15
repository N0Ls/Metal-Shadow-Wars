#include "unit.hpp"
#include <iostream>
using namespace std;
#include <string.h>
#include "constants.hpp"
#include <math.h>



void initUnit(unit *unit, int id,float pv,float force,float dexterity, float fireRange, int arrayIndex, GLuint texture_id){
  unit -> ownerId = id;
  unit -> pv = pv;
  unit -> force = force;
  unit -> dexterity = dexterity;
  unit -> fireRange = fireRange;
  unit -> isAlive = true;
  unit -> arrayIndex = arrayIndex;
  unit -> texture_id = texture_id;
}

void setCoordinates(unit *unit, int x, int y){
  unit -> x = x;
  unit -> y = y;
}

void updateDisplayCoordinates(unit *unit){
  unit -> displayX = (-GL_VIEW_SIZE/2)+unit->x*MAP_TILE_SIZE;
  unit -> displayY = (-GL_VIEW_SIZE/2)+unit->y*MAP_TILE_SIZE;
}

void drawQuadUnit(){
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

void displayUnit(unit *unit, GLuint textureIds_units[]){
  glPushMatrix();
  glScalef(1,-1,1.);
  float destinationDisplayX = (-GL_VIEW_SIZE/2)+unit->x*MAP_TILE_SIZE;
  float destinationDisplayY = (-GL_VIEW_SIZE/2)+unit->y*MAP_TILE_SIZE;

  if(unit -> displayX < destinationDisplayX){
    unit ->displayX = unit->displayX + 0.1;
  }
  if(unit -> displayX > destinationDisplayX){
    unit ->displayX = unit->displayX - 0.1;
  }

  if(unit->displayY < destinationDisplayY){
    unit ->displayY = unit->displayY + 0.1;
  }
  if(unit->displayY > destinationDisplayY){
    unit ->displayY = unit->displayY - 0.1;
  }
  glTranslatef(unit->displayX, unit->displayY,0);
  glBindTexture(GL_TEXTURE_2D, textureIds_units[unit->texture_id]);
  //glRotatef(90,0,0,1);
  drawQuadUnit();

  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D, 0);
}

void deplacement(unit *unit , int destinationX, int destinationY){
  unit->x = destinationX;
  unit->y = destinationY;
}

void printUnitInfos(unit *unit){
  cout << "Cette unité se situe en"<< unit->x <<", "<< unit->y << '\n';
  cout << "Cette unité utilise la texture"<< unit->texture_id << '\n';
}
