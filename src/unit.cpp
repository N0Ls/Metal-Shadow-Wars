#include "unit.hpp"
#include <iostream>
using namespace std;
#include <string.h>


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
