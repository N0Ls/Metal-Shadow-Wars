#ifndef UNIT_H
#define UNIT_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

typedef struct {
    int ownerId;
    float pv;
    int x;
    int y ;
    int arrayIndex;
    bool isAlive;
    float force;
    float dexterity;
    float fireRange;
    GLuint texture_id;
} unit;

//Declaration of prototypes
void initUnit(unit *unit, int id,float pv,float force,float dexterity, float fireRange, int arrayIndex, GLuint texture_id);
void setCoordinates(unit *unit, int x, int y);
void displayUnit(unit *unit, GLuint textureIds_units[]);
void printUnitInfos(unit *unit);

#endif
