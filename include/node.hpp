#ifndef NODE_H
#define NODE_H

struct Node{
  int x,y;
  double heuristic, g_cost, f_weight;
  Node* parent;
  Node* children;
};

void initNode(Node *node, int x, int y);

void displayNode(Node node);

bool isValid(int x, int y);
bool isDestination(int x, int y, Node node_destination);

double calculateHeuristic(int x, int y, Node node_destination);


void generateNodeTab(int map[][MAP_SIZE], Node* nodeMap[]);

void aStar(int map[][MAP_SIZE], int xStart, int yStart, int xDest, int yDest);

#endif
