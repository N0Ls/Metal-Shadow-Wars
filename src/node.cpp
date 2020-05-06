#include "constants.hpp"
#include "node.hpp"
#include <stdlib.h>

bool isValid(int x, int y)
{
    if(!(x>0 && y>0 && x<=MAP_SIZE && y<=MAP_SIZE)){
      return 1;
    }
    else{
      return 0;
    }
}

bool isDestination(int x, int y, Node node_destination)
{
    if (x == node_destination.x && y == node_destination.y)
        return (true);
    else
        return (false);
}

double calculateHeuristic(int x, int y, Node node_destination)
{
  return abs (x - node_destination.x) + abs (y - node_destination.y);
}
