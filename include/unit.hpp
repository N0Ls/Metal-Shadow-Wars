#ifndef UNIT_H
#define UNIT_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stack>
#include <vector>
#include "node.hpp"
using namespace std;

struct player;
struct Unit{
    int ownerId;
    player *ownerPlayer;
    float pv;
    float pvMax;
    int x;
    int y ;
    float displayX;
    float displayY;
    int arrayIndex;

    bool isAlive;
    bool isMoving;
    bool isMovingToNextTile=false;
    bool hasToAttack=false;
    bool isDONE=false;

    float force;
    float dexterity;
    float fireRange;
    GLuint texture_id;
    stack <PathCoordinates> currentPath;
    PathCoordinates currentDestination;
};


//Declaration of prototypes
void initUnit(Unit *unit, int id, player *owner, float pv,float force,float dexterity, float fireRange, int arrayIndex, GLuint texture_id);
void setCoordinates(Unit *unit, int x, int y);
void displayUnit(Unit *unit, GLuint textureIds_units[]);
void printUnitInfos(Unit *unit);
void updateDisplayCoordinates(Unit *unit);
void deplacement(Unit *unit , int destinationX, int destinationY);
void attackUnit(Unit *attacker, Unit *defender);
void autoMove(Unit *unit, int tab[], vector<Unit> &unitRef);

#endif
