#include "unit.hpp"
#include <iostream>
using namespace std;
#include <string.h>
#include "constants.hpp"
#include <math.h>
#include <SDL/SDL.h>
#include <stack>
#include "node.hpp"
#include "player.hpp"

void initUnit(unit *unit, int id, player *owner, float pv,float force,float dexterity, float fireRange, int arrayIndex, GLuint texture_id){
  unit -> ownerId = id;
  unit -> ownerPlayer = owner;
  unit -> pv = pv;
  unit -> pvMax = pv;
  unit -> force = force;
  unit -> dexterity = dexterity;
  unit -> fireRange = fireRange;
  unit -> isAlive = true;
  unit -> isMoving = false;
  unit -> arrayIndex = arrayIndex;
  unit -> texture_id = texture_id;
}

void setCoordinates(unit *unit, int x, int y){
  unit -> x = x;
  unit -> y = y;
}

void updateDisplayCoordinates(unit *unit){

  float destinationDisplayX;
  float destinationDisplayY;
  float speed = 0.15;
  if(!(unit->currentPath.empty())){
    if(unit->isMovingToNextTile ==true){
      destinationDisplayX = (-GL_VIEW_SIZE/2)+unit->currentDestination.x*MAP_TILE_SIZE;
      destinationDisplayY = (-GL_VIEW_SIZE/2)+unit->currentDestination.y*MAP_TILE_SIZE;

      //déplacement de l'unité
      if(unit -> displayX < destinationDisplayX){
        unit ->displayX = unit->displayX + speed;
      }
      if(unit -> displayX > destinationDisplayX){
        unit ->displayX = unit->displayX - speed;
      }

      if(unit->displayY < destinationDisplayY){
        unit ->displayY = unit->displayY + speed;
      }
      if(unit->displayY > destinationDisplayY){
        unit->displayY = unit->displayY - speed;
      }

      //on vérifie si on est arrivé sur la case
      if(unit->displayX > (destinationDisplayX-0.2) && unit->displayX < (destinationDisplayX+0.2) && unit->displayY >(destinationDisplayY-0.2) && unit->displayY <(destinationDisplayY+0.2)){
        cout <<"on est arrivé à la case"<< endl;
        //on arrondie la position pour être sur une valeur entière
        unit->displayX = (-GL_VIEW_SIZE/2)+unit->currentDestination.x*MAP_TILE_SIZE;
        unit->displayY = (-GL_VIEW_SIZE/2)+unit->currentDestination.y*MAP_TILE_SIZE;

        unit->isMovingToNextTile = false;
        unit->currentPath.pop();
      }
    }
    else{
      unit->isMovingToNextTile =true;
      unit->currentDestination = unit->currentPath.top();
    }
  }
  else{
    cout << "Chemin terminé" << endl;
    unit->isMoving=false;
  }

}

void drawQuadUnit(){
  glBegin(GL_QUADS);
    //glColor3f(1,1,1);
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

  if(unit->isMoving ==true){
    updateDisplayCoordinates(unit);
  }
  glTranslatef(unit->displayX, unit->displayY,0);
  glBindTexture(GL_TEXTURE_2D, textureIds_units[unit->texture_id]);
  //glRotatef(90,0,0,1);
  glColor3f(unit->ownerPlayer->color.r,unit->ownerPlayer->color.g,unit->ownerPlayer->color.b);
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
  //cout << "Cette unité appartient à "<< unit->ownerPlayer->name << '\n';
}

void attackUnit(unit *attacker, unit *defender)
{
    // When call, attacker correspond to the selected unit,
    // and the defender to the unit corresponding to the position where the click happened.
    defender->pv -= attacker->force * attacker->pv/(float)attacker->pvMax;
    if (defender->pv <= 0)
    {
        std::cout << "Defender is dead." << std::endl;
        // Retirer l'unité de la liste des unités du joueur
    }
    //attacker->state = DONE;
}
