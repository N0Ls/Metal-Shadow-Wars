#ifndef UNIT_H
#define UNIT_H

using namespace std;
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stack>

typedef struct {
    int ownerId;
    float pv;
    int x;
    int y ;
    float displayX;
    float displayY;
    int arrayIndex;
    bool isAlive;
    bool isMoving;
    float force;
    float dexterity;
    float fireRange;
    GLuint texture_id;
    stack <PathCoordinates> currentPath;
} unit;

//Declaration of prototypes
void initUnit(unit *unit, int id,float pv,float force,float dexterity, float fireRange, int arrayIndex, GLuint texture_id);
void setCoordinates(unit *unit, int x, int y);
void displayUnit(unit *unit, GLuint textureIds_units[]);
void printUnitInfos(unit *unit);
void updateDisplayCoordinates(unit *unit);
void deplacement(unit *unit , int destinationX, int destinationY);
#endif
