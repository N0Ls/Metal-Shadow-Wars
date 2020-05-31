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

/**
 *
 * Initialize Unit atttributes.
 *
 * @param unit The unit to initialize.
 * @param id The id of the player that owns the unit.
 * @param owner The reference to the player that owns the unit.
 * @param pv The number of health points of the unit.
 * @param force The force of the unit (its fire power).
 * @param dexterity The dexterity of the unit (its mobility on the map).
 * @param fireRange The range of the attack of the unit.
 * @param arrayIndex The index of the unit inside the unit vector of the player.
 * @param textureId The id of the texture that the unit use
 *
 */
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

  TTF_Font *font2 =TTF_OpenFont("./assets/fonts/ChelseaMarket-Regular.ttf", 15);
  SDL_Color couleurTXT = {255,255, 255};
  //unit->surfaceText=NULL;
  char pvChar[10];
  sprintf(pvChar, "%d", (int)unit->pv);
  createText(unit->surfaceText,font2, unit->textureText, pvChar, couleurTXT);
  TTF_CloseFont(font2);
}


/**
 *
 * Setting the unit atttributes to correspond to a robot.
 *
 * @param unit The unit to modify.
 *
 */
void initRobot(Unit *unit){
  unit->pv = 150;
  unit->force = 75;
  unit->dexterity = 2;
  unit->fireRange=2;
  unit->texture_id = 1;
}


/**
 *
 * Setting the unit atttributes to correspond to a dog.
 *
 * @param unit The unit to modify.
 *
 */
void initDog(Unit *unit){
  unit->pv = 120;
  unit->force = 60;
  unit->dexterity = 4;
  unit->fireRange=1;
  unit->texture_id = 2;
}


/**
 *
 * Set the coordinates of a unit.
 *
 * @param unit The unit to modify.
 * @param x The x coordinate value.
 * @param y The y coordinate value.
 *
 */
void setCoordinates(Unit *unit, int x, int y){
  unit -> x = x;
  unit -> y = y;
}


/**
 *
 * Set the new coordinates of a unit.
 *
 * @param unit The unit to modify.
 * @param x The x coordinate value.
 * @param y The y coordinate value.
 *
 */
void deplacement(Unit *unit , int destinationX, int destinationY){
  unit->x = destinationX;
  unit->y = destinationY;
}


/**
 *
 * Function to make the unit move smoothly
 *
 * @param unit The unit moving.
 *
 */
void updateDisplayCoordinates(Unit *unit){

  float destinationDisplayX;
  float destinationDisplayY;
  float speed = 0.15;

  //checking if the unit movement is finished
  if(!(unit->currentPath.empty())){
    //Checking if unit is already moving from one tile to another
    if(unit->isMovingToNextTile ==true){
      //Where the unit is supposed to be
      destinationDisplayX = (-GL_VIEW_SIZE/2)+unit->currentDestination.x*MAP_TILE_SIZE;
      destinationDisplayY = (-GL_VIEW_SIZE/2)+unit->currentDestination.y*MAP_TILE_SIZE;

      //Moving the unit
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

      //Checking if we are on the tile
      if(unit->displayX > (destinationDisplayX-0.2) && unit->displayX < (destinationDisplayX+0.2) && unit->displayY >(destinationDisplayY-0.2) && unit->displayY <(destinationDisplayY+0.2)){
        //rounding the value so we are on a precise position
        unit->displayX = (-GL_VIEW_SIZE/2)+unit->currentDestination.x*MAP_TILE_SIZE;
        unit->displayY = (-GL_VIEW_SIZE/2)+unit->currentDestination.y*MAP_TILE_SIZE;

        unit->isMovingToNextTile = false;
        unit->currentPath.pop(); //removing the current tile
      }
    }
    else{
      //picking the next destination tile in the stack
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


/**
 *
 * Function to draw the quads unit
 *
 */
void drawQuadUnit(){
  glBegin(GL_QUADS);
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


/**
 *
 * Display the unit.
 *
 * @param unit The unit to display.
 * @param textureIds_units[] The array containing the texturesIds
 *
 */
void displayUnit(Unit *unit, GLuint textureIds_units[]){

  float step = 100/MAP_SIZE;

  displayText(unit->surfaceText, *unit->textureText,unit->displayX+step/2, unit->displayY-step/2);

  glClearColor(0, 0, 0, 0);
  glPushMatrix();
  glScalef(1,-1,1.);

  if(unit->isMoving ==true){
    updateDisplayCoordinates(unit);
  }
  //translating to correct place
  glTranslatef(unit->displayX, unit->displayY,0);
  glBindTexture(GL_TEXTURE_2D, textureIds_units[unit->texture_id]);

  //coloring the unit
  if(unit->isDONE==false){
    glColor4f((float) unit->ownerPlayer->color.r/255,(float)unit->ownerPlayer->color.g/255,(float)unit->ownerPlayer->color.b/255,1);
  }
  else{
    glColor3f(1,1,1);
  }
  drawQuadUnit();
  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D, 0);
}


/**
 *
 * Print the unit infos in the console.
 *
 * @param unit The unit to display infos from.
 *
 */
void printUnitInfos(Unit *unit){
  cout << "Cette unité se situe en"<< unit->x <<", "<< unit->y << '\n';
  cout << "Cette unité utilise la texture"<< unit->texture_id << '\n';
  //cout << "Cette unité appartient à "<< unit->ownerPlayer->name << '\n';
}


/**
 *
 * Attack between two units.
 *
 * @param attacker The attacking unit
 * @param defender The defending unit
 *
 */
void attackUnit(Unit *attacker, Unit *defender)
{
    // When call, attacker correspond to the selected unit,
    // and the defender to the unit corresponding to the position where the click happened.
    int damages = attacker->force * attacker->pv/(float)attacker->pvMax;
    defender->pv -= damages;
    cout << "Aie j'ai pris " << damages << " dégats dans les dents ! " << endl;
    updateTextUnit(defender);
    //Checking is the defender is dead
    if (defender->pv <= 0)
    {
        defender->isAlive=false;
        std::cout << "Defender is dead." << std::endl;
        player *playerMourning = defender->ownerPlayer;
        //removing the unit from the player's unit list
        playerMourning->units.erase(playerMourning->units.begin()+defender->arrayIndex);
        playerMourning->nbUnits=playerMourning->units.size();
        updateUnitIndex(playerMourning);
    }
}

/**
 *
 * Automatic move for AI units
 *
 * @param unit The unit to move.
 * @param tab[] The array containing all the tiles of the map.
 * @param unitRef The vector of units in the game
 *
 */
void autoMove(Unit *unit, TileMap tab[],vector<Unit*> &unitRef)
{
  //chosing a destination tile
  cout << "Unité en : " << unit->x << " : " << unit->y << endl;
  vector <PathCoordinates> possibleTile;
  for(int x=(unit->x-unit->dexterity); x < (unit->x+unit->dexterity); x++){
    for(int y=(unit->y-unit->dexterity); y < (unit->y+unit->dexterity); y++){
      if((x >=0 && x < MAP_SIZE && y>=0&& y<MAP_SIZE)){
        if(abs(unit->x - x) + abs(unit->y - y) <= unit->dexterity && (tab[x*MAP_SIZE + y].isWalkable) && !(unit->x ==x && unit->y ==y)){
          PathCoordinates NewCoord;
          NewCoord.x=x;
          NewCoord.y=y;
          possibleTile.push_back(NewCoord);
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
  //searching the closest unit
  Unit* closestUnit = NULL; //to correct segFault
  Unit* currentUnit = NULL;
  int closestDistance = MAP_SIZE+MAP_SIZE;

  for(int l=0; l<(int)unitRef.size(); l++){
    currentUnit=unitRef[l];
    int currentDistance = abs(unit->x - currentUnit->x) + abs(unit->y - currentUnit->y);
    if(currentDistance<=closestDistance && currentUnit->ownerId != unit->ownerId){
      closestUnit=currentUnit;
      closestDistance=currentDistance;
    }
  }
  if(closestUnit!=NULL){
      cout << "closest Unit to " << unit->x << ":" << unit->y << "   is  " << closestUnit->x << ":" << closestUnit->y<< endl;
  }
  else{
    cout << "closest null" << endl;
  }
  if(closestUnit!=NULL){
    srand(time(NULL)+rand());
    int randIndex = rand() % possibleTile.size();

    PathCoordinates closestTile = possibleTile[(int)randIndex];
    int closestDistanceTiles = abs(closestUnit->x - closestTile.x) + abs(closestUnit->y - closestTile.y);

    for(int j = 0 ; j<(int)possibleTile.size(); j++){
      PathCoordinates currentCoordTiles=possibleTile[j];
      int currentDistanceTiles = abs(closestUnit->x - currentCoordTiles.x) + abs(closestUnit->y - currentCoordTiles.y);
      if(currentDistanceTiles < closestDistanceTiles){
        closestTile.x = currentCoordTiles.x;
        closestTile.y = currentCoordTiles.y;
        closestDistanceTiles=currentDistanceTiles;
      }
    }
    cout << "closest Tile to " << closestUnit->x << ":" << closestUnit->y << "   is  " << closestTile.x << ":" << closestTile.y<< endl;

    unit->currentPath = aStar(tab, unit->x, unit->y, closestTile.x, closestTile.y);
    unit->isMoving =true;

    deplacement(unit, closestTile.x, closestTile.y);
    //unit->hasToAttack =true;
  }
  else{
    //When NULL using a random tile
    srand(time(NULL)+rand());
    int randIndex = rand() % possibleTile.size();
    PathCoordinates randomTile = possibleTile[randIndex];

    unit->currentPath = aStar(tab, unit->x, unit->y, randomTile.x, randomTile.y);
    unit->isMoving =true;

    deplacement(unit, randomTile.x, randomTile.y);
    //unit->hasToAttack =true;
  }

}

/**
 *
 * Automatic attack for AI units
 *
 * @param unit The unit to move.
 * @param tab[] The array containing all the tiles of the map.
 * @param unitRef The vector of units in the game
 *
 */
void autoAttack(Unit *unit, TileMap tab[], vector<Unit*> &unitRef){
  //privileging units in range
  unit->hasToAttack=false;
  for(int w = 0 ; w<(int)unitRef.size(); w++){
    if(abs(unit->x - unitRef[w]->x) + abs(unit->y - unitRef[w]->y) <= unit->fireRange && !(unit->x ==unitRef[w]->x && unit->y ==unitRef[w]->y) && unit->ownerId != unitRef[w]->ownerId){
      attackUnit(unit, unitRef[w]);
      unit->isDONE=true;
      cout << "Joueur clavier attaqué" << endl;
      return;
    }
  }
  unit->isDONE=true;
}

/**
 *
 * Update the text above the unit
 *
 * @param unit The unit we want to update the text.
 *
 */
void updateTextUnit(Unit *unit){
  TTF_Font *font2 =TTF_OpenFont("./assets/fonts/ChelseaMarket-Regular.ttf", 15);
  SDL_Color couleurTXT = {255,255, 255};
  char pvChar[10];
  sprintf(pvChar, "%d", (int)unit->pv);
  createText(unit->surfaceText,font2, unit->textureText, pvChar, couleurTXT);
  TTF_CloseFont(font2);
}
