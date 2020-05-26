#include "unit.hpp"
#include <iostream>
using namespace std;
#include <string.h>
#include "constants.hpp"
#include <math.h>
#include <SDL/SDL.h>
#include <stack>
#include <vector>
#include "node.hpp"
#include "player.hpp"

void initUnit(Unit *unit, int id, player *owner, float pv,float force,float dexterity, float fireRange, int arrayIndex, GLuint texture_id){
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

void setCoordinates(Unit *unit, int x, int y){
  unit -> x = x;
  unit -> y = y;
}

void updateDisplayCoordinates(Unit *unit){

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
    unit->hasToAttack=true;
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


void displayUnit(Unit *unit, GLuint textureIds_units[]){
  glClearColor(0, 0, 0, 0);
  glPushMatrix();
  glScalef(1,-1,1.);

  if(unit->isMoving ==true){
    updateDisplayCoordinates(unit);
  }
  glTranslatef(unit->displayX, unit->displayY,0);
  glBindTexture(GL_TEXTURE_2D, textureIds_units[unit->texture_id]);
  //glRotatef(90,0,0,1);
  if(unit->isDONE==false){
    glColor4f(unit->ownerPlayer->color.r,unit->ownerPlayer->color.g,unit->ownerPlayer->color.b,1);
  }
  else{
    glColor3f(1,1,1);
  }
  drawQuadUnit();

  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D, 0);
}

void deplacement(Unit *unit , int destinationX, int destinationY){
  unit->x = destinationX;
  unit->y = destinationY;
}

void printUnitInfos(Unit *unit){
  cout << "Cette unité se situe en"<< unit->x <<", "<< unit->y << '\n';
  cout << "Cette unité utilise la texture"<< unit->texture_id << '\n';
  //cout << "Cette unité appartient à "<< unit->ownerPlayer->name << '\n';
}

void attackUnit(Unit *attacker, Unit *defender)
{
    // When call, attacker correspond to the selected unit,
    // and the defender to the unit corresponding to the position where the click happened.
    int damages = attacker->force * attacker->pv/(float)attacker->pvMax;
    //int damages = defender->pv
    defender->pv -= damages;
    cout << "Aie j'ai pris " << damages << " dégats dans les dents ! " << endl;
    if (defender->pv <= 0)
    {
        defender->isAlive=false;
        std::cout << "Defender is dead." << std::endl;
        player *playerMourning = defender->ownerPlayer;
        playerMourning->units.erase(playerMourning->units.begin()+defender->arrayIndex);
        playerMourning->nbUnits=playerMourning->units.size();
        // Retirer l'unité de la liste des unités du joueur
    }
}

void autoMove(Unit *unit, int tab[],vector<Unit*> &unitRef)
{
  //calcul d'une case d'arrivé
  cout << "Unité en : " << unit->x << " : " << unit->y << endl;
  vector <PathCoordinates> possibleTile;
  for(int x=(unit->x-unit->dexterity); x < (unit->x+unit->dexterity); x++){
    for(int y=(unit->y-unit->dexterity); y < (unit->y+unit->dexterity); y++){
      if((x >=0 && x < MAP_SIZE && y>=0&& y<MAP_SIZE)){
        if(abs(unit->x - x) + abs(unit->y - y) <= unit->dexterity && (tab[x*MAP_SIZE + y]==2) && !(unit->x ==x && unit->y ==y)){
          PathCoordinates NewCoord;
          NewCoord.x=x;
          NewCoord.y=y;
          possibleTile.push_back(NewCoord);
          cout << "adding the tile " << x << " : " << y << endl;
        }
      }
    }
  }

  //removing tiles with unit on it
  for(int z = 0 ; z<(int)possibleTile.size(); z++){
    for(int w = 0 ; w<(int)unitRef.size(); w++){
      PathCoordinates currentCoord=possibleTile[z];
      Unit* unitToCheck = unitRef[w];
      if(currentCoord.x == unitToCheck->x && currentCoord.y==unitToCheck->y){
        possibleTile.erase(possibleTile.begin()+z);
      }
    }
  }

  srand(time(NULL)+rand());
  int randIndex = rand() % possibleTile.size();
  PathCoordinates randomTile = possibleTile[randIndex];
  cout << endl << "selected " << randomTile.x << " : "  << randomTile.y <<endl;
    cout << endl<< endl;


  unit->currentPath = aStar(tab, unit->x, unit->y, randomTile.x, randomTile.y);
  unit->isMoving =true;

  deplacement(unit, randomTile.x, randomTile.y);
  // unit->displayX = (-GL_VIEW_SIZE/2)+unit->x*MAP_TILE_SIZE;
  // unit->displayY = (-GL_VIEW_SIZE/2)+unit->y*MAP_TILE_SIZE;
  unit->hasToAttack =true;

  //unit->isDONE=true;
}
void autoAttack(Unit *unit, int tab[], vector<Unit*> &unitRef){
  //privielging
  //checking units
  for(int w = 0 ; w<(int)unitRef.size(); w++){
    if(abs(unit->x - unitRef[w]->x) + abs(unit->y - unitRef[w]->y) <= unit->fireRange && !(unit->x ==unitRef[w]->x && unit->y ==unitRef[w]->y)){
      attackUnit(unit, unitRef[w]);
      unit->isDONE=true;
      cout << "Joueur clavier attaqué" << endl;
      return;
    }
  }
  unit->isDONE=true;
}
