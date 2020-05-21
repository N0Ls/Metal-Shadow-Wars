#ifndef UNIT_H
#define UNIT_H

using namespace std;
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stack>
#include "node.hpp"

typedef struct {
    int ownerId;
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
    float force;
    float dexterity;
    float fireRange;
    GLuint texture_id;
    stack <PathCoordinates> currentPath;
    PathCoordinates currentDestination;
} unit;

//Declaration of prototypes
void initUnit(unit *unit, int id,float pv,float force,float dexterity, float fireRange, int arrayIndex, GLuint texture_id);
void setCoordinates(unit *unit, int x, int y);
void displayUnit(unit *unit, GLuint textureIds_units[]);
void printUnitInfos(unit *unit);
void updateDisplayCoordinates(unit *unit);
void deplacement(unit *unit , int destinationX, int destinationY);
void attackUnit(unit *attacker, unit *defender);

#endif
