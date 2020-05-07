#include "constants.hpp"
#include "node.hpp"
#include <stdlib.h>
using namespace std;
#include <iostream>

void initNode(Node *node, int x, int y)
{
  node->x=x;
  node->y=y;
}

void displayNode(Node node){
  std::cout << node.x<< " , " << node.y << '\n';
}

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

int maze[MAP_SIZE][MAP_SIZE] = {
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
};

// void generateNodeTab(int map[][MAP_SIZE], Node nodeMap[]){
//   for (int j = 0; j < MAP_SIZE; j++) {
//     for (int k = 0; k < MAP_SIZE; k++) {
//       initNode(nodeMap[j*MAP_SIZE +k],j,k);
//     }
//   }
// }

void aStar(int map[][MAP_SIZE], int xStart, int yStart, int xDest, int yDest){
  Node nodeMap[MAP_SIZE*MAP_SIZE];

  Node** nodeMapPTR;
  nodeMapPTR =(Node**) malloc(100 * sizeof(Node*));


  for (int j = 0; j < MAP_SIZE; j++) {
    for (int k = 0; k < MAP_SIZE; k++) {
      initNode(&nodeMap[j*MAP_SIZE +k],j,k);
      displayNode(nodeMap[j*MAP_SIZE +k]);
      cout<< &nodeMap[j*MAP_SIZE +k]<<endl;
      nodeMapPTR[j*MAP_SIZE +k] = &nodeMap[j*MAP_SIZE +k];
    }
  }

  for (int a = 0; a < 100; a++) {
    displayNode(nodeMap[a]);
    displayNode(*nodeMapPTR[a]);
  }
  // std::cout << &nodeMap[1] << '\n';
  // displayNode(nodeMap[1]);
  // nodeMapPTR[99] = &nodeMap[99];
  // displayNode(nodeMapPTR+99);

  //initNode(&nodeMap+0,1,1);
  free(nodeMapPTR);
}
//function to generate the tab of nodes
