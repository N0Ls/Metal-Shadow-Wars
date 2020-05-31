#include <stdlib.h>
#include <limits>
#include <iostream>
#include <stack>
#include "constants.hpp"
#include "node.hpp"
using namespace std;


/**
 *
 * Initialize the nodes values
 *
 * @param node The node we want to initialize.
 * @param x The x value of the node.
 * @param y The y value of the node.
 *
 */
void initNode(Node *node, int x, int y)
{
  node->x=x;
  node->y=y;
}


/**
 *
 * Sets the validity of the node
 *
 * @param node The node we want to set.
 * @param validity The validity of the node.
 *
 */
void setValidity(Node *node, bool validity)
{
  node->validity=validity;
}


/**
 *
 * Display the node infos in the console.
 *
 * @param node The node to display.
 *
 */
void displayNode(Node node){
  std::cout << node.x<< " , " << node.y << " is valid : " << node.validity <<'\n';
}


/**
 *
 * Function to know if the node is valid or not
 *
 * @param x The x coordinate of the node.
 * @param y The y coordinate of the node.
 * @param map The reference to the tiles.
 *
 * @return True or false according the validity of the node.
 *
 */
bool isValid(int x, int y, TileMap map[MAP_SIZE*MAP_SIZE])
{
    if((x>=0 && y>=0 && x<MAP_SIZE && y<MAP_SIZE) && (map[(x)*MAP_SIZE+ y].isWalkable)){
      return 1;
    }
    else{
      return 0;
    }
}


/**
 *
 * Checks if the node is the destination
 *
 * @param x The x coordinate of the node.
 * @param y The y coordinate of the node.
 * @param node_destination The destination node.
 *
 * @return True or false according if we arrived or not.
 *
 */
bool isDestination(int x, int y, Node node_destination)
{
    if (x == node_destination.x && y == node_destination.y)
        return (true);
    else
        return (false);
}


/**
 *
 * Calculate the heuristic (distance) value between two nodes
 *
 * @param x The x coordinate of the node.
 * @param y The y coordinate of the node.
 * @param node_destination The destination node.
 *
 * @return The heuristic value.
 *
 */
double calculateHeuristic(int x, int y, Node node_destination)
{
  return abs (x - node_destination.x) + abs (y - node_destination.y);
}


/**
 *
 * Insert a node into a linked list
 *
 * @param liste The list we want to add the node into.
 * @param nvNode The node to add to the list.
 *
 *
 */
void insertion(Liste *liste, Node *nvNode)
{
  /* Create new element */
  Element *nouveau = (Element *) malloc(sizeof(Element *));
  if (liste == NULL || nouveau == NULL)
  {
      exit(EXIT_FAILURE);
  }
  nouveau->node = nvNode;
  nouveau->next = liste->first;
  liste->first = nouveau;
}


/**
 *
 * Display the list elements
 *
 * @param liste The list we want to display.
 *
 *
 */
void afficherListe(Liste *liste)
{
    cout << "voici la liste" << endl;
    if (liste == NULL)
    {
      cout<<"erreur liste"<<endl;
      exit(EXIT_FAILURE);
    }
    if(liste->first == NULL){
      cout<< "listevide"<<endl;
      return;
    }

    Element *current = (Element *) malloc(sizeof(Element *));
    current = liste->first;

    while (current != NULL)
    {
      //displayNode(*current->node);
      current = current->next;
    }
    free(current);
}

/**
 *
 * Delete a node from a linked list
 *
 * @param liste The list we want to delete the node from.
 * @param nvNode The node we want to delete from the list.
 *
 *
 */
void deleteNode(Liste *l, Node nodeToDelete)
{
    Element *tmp = (Element *) malloc(sizeof(Element *));
    Element *prev = (Element *) malloc(sizeof(Element *));

    tmp = l->first;

    if (tmp != NULL && tmp->node->x == nodeToDelete.x && tmp->node->y == nodeToDelete.y)
    {
        l->first = tmp->next;
        return;
    }
    while (tmp != NULL && ((tmp->node->y != nodeToDelete.y)||(tmp->node->x != nodeToDelete.x)))
    {
        prev = tmp;
        tmp = tmp->next;
    }

    if (tmp == NULL){
      return;
    }
    // Unlink the node from linked list
    prev->next = tmp->next;

}

/**
 *
 * Searches a node inside a linked list
 *
 * @param liste The list to search.
 * @param nvNode The node we search in the list.
 *
 * @return True if the node is in the list. False otherwise
 *
 */
bool isNodeExisting(Liste *l, Node *nodeToSearch){
  if (l == NULL)
  {
      exit(EXIT_FAILURE);
  }
  Element *current = (Element *) malloc(sizeof(Element *));
  current = l->first;

  while (current != NULL)
  {
    if(current->node->x == nodeToSearch->x && current->node->y == nodeToSearch->y){
      return 1;
    }
    current = current->next;
  }
  free(current);
  return 0;
}


/**
 *
 * Finds the node with the lowest cost for a star.
 *
 * @param liste The list that contains the nodes
 *
 * @return The cheapeast node of the list.
 *
 */
Node *findcheapestNode(Liste *l){
  if (l == NULL)
  {
      exit(EXIT_FAILURE);
  }

  Element *currentElement = (Element *) malloc(sizeof(Element *));
  currentElement = l->first;

  int minF = std::numeric_limits<int>::max();

  Node *cheapestNode = (Node *) malloc(sizeof(Node *));

  while (currentElement != NULL)
  {
    if(minF>currentElement->node->f){
      minF=currentElement->node->f;
      cheapestNode=currentElement->node;
      //cout << "Le noeud le plus cheap est : ";
      //displayNode(*cheapestNode);
    }
    currentElement = currentElement->next;
  }
  free(currentElement);
  return cheapestNode;
}


/**
 *
 * Sets the node values according to the current parameters.
 *
 * @param nodeToSet The node we need to modify.
 * @param current The current node.
 * @param dest The destination node.
 *
 *
 */
void setNodeValues(Node *nodeToSet, Node current,Node dest){
  nodeToSet->g = (current.g)+1;
  nodeToSet->h = calculateHeuristic(nodeToSet->x, nodeToSet->y,dest);
  nodeToSet->f=nodeToSet->g+nodeToSet->h;
}


/**
 *
 * A star pathfinding algorithm
 *
 * @param map The map reference.
 * @param xStart The x starting coordinate.
 * @param yStart The y starting coordinate.
 * @param xDest The x coordinate for the destination.
 * @param yDest The y coordinate for the destination.
 *
 * @return Return a stack of tiles that constitute the path.
 *
 */
std::stack <PathCoordinates> aStar(TileMap map[MAP_SIZE*MAP_SIZE], int xStart, int yStart, int xDest, int yDest){
  Node nodeMap[MAP_SIZE*MAP_SIZE];
  stack <PathCoordinates> path;

  //Check if start and finish are the same
  if(xStart==xDest && yStart==yDest){
    return path;
  }

  //translating the map into nodes
  for (int j = 0; j < MAP_SIZE; j++) {
    for (int k = 0; k < MAP_SIZE; k++) {
      initNode(&nodeMap[j*MAP_SIZE +k],j,k);
      setValidity(&nodeMap[j*MAP_SIZE +k],map[j*MAP_SIZE+k].isWalkable);
    }
  }

  //Initialization of the important nodes
  Node *startingNode = &nodeMap[xStart*MAP_SIZE +yStart];
  Node *destNode = &nodeMap[xDest*MAP_SIZE +yDest];
  Node *currentNode = startingNode;

  // displayNode(*startingNode);
  // displayNode(*destNode);

  if(destNode->validity == false){
    std::cout << "case non valide" << '\n';
    return path;
  }

  //Creation of the linked list
  Liste *visited = (Liste *) malloc(sizeof(Liste *));
  Liste *toVisit = (Liste *) malloc(sizeof(Liste *));

  if (visited == NULL || toVisit == NULL ){exit(EXIT_FAILURE);}

  Element *elementStart = (Element *) malloc(sizeof(Element *));

  //Initializing lists
  startingNode->f=0;
  startingNode->parent =NULL;
  elementStart->node = startingNode;
  elementStart->next = NULL;

  toVisit->first = NULL;
  visited->first = elementStart;

  //visiting neighbors
  if(isValid(currentNode->x+1,currentNode->y,map) && !(isNodeExisting(visited,&nodeMap[(currentNode->x+1)*MAP_SIZE +currentNode->y]))){
    nodeMap[(currentNode->x+1)*MAP_SIZE +currentNode->y].parent = currentNode;
    setNodeValues(&nodeMap[(currentNode->x+1)*MAP_SIZE +currentNode->y],*currentNode,*destNode);
    insertion(toVisit,&nodeMap[(currentNode->x+1)*MAP_SIZE +currentNode->y]);
  }
  if(isValid(currentNode->x-1,currentNode->y,map) && !(isNodeExisting(visited,&nodeMap[(currentNode->x-1)*MAP_SIZE +currentNode->y]))){
    nodeMap[(currentNode->x-1)*MAP_SIZE +currentNode->y].parent = currentNode;
    setNodeValues(&nodeMap[(currentNode->x-1)*MAP_SIZE +currentNode->y],*currentNode,*destNode);
    insertion(toVisit,&nodeMap[(currentNode->x-1)*MAP_SIZE +currentNode->y]);
  }
  if(isValid(currentNode->x,currentNode->y-1,map) && !(isNodeExisting(visited,&nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y-1)]))){
    nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y-1)].parent = currentNode;
    setNodeValues(&nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y-1)],*currentNode,*destNode);
    insertion(toVisit,&nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y-1)]);
  }
  if(isValid(currentNode->x,currentNode->y+1,map)&& !(isNodeExisting(visited,&nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y+1)]))){
    nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y+1)].parent = currentNode;
    setNodeValues(&nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y+1)],*currentNode,*destNode);
    insertion(toVisit,&nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y+1)]);
  }

  /* A-STAR LOOP */
  bool found = 0;
  while(found==0 && toVisit->first !=NULL){

    //searching for the cheapeast node
    currentNode = findcheapestNode(toVisit);
    //cout <<"cheapestNode : " ;
    //displayNode(*currentNode);
    deleteNode(toVisit,*currentNode);
    insertion(visited,currentNode);

    // afficherListe(visited);
    // afficherListe(toVisit);

    //Checking if we arrived to destination
    if(currentNode->x == destNode->x && currentNode->y == destNode->y){
      cout<<"trouvé" << endl;
      found=1;
    }

    else{
      //cout << "pas encore trouvé"<<endl;
    }

    //Visiting the neighbors (UP - DOWN - LEFT - RIGHT)
    if(isValid(currentNode->x+1,currentNode->y, map) && !(isNodeExisting(visited,&nodeMap[(currentNode->x+1)*MAP_SIZE +currentNode->y]))){

      nodeMap[(currentNode->x+1)*MAP_SIZE +currentNode->y].parent = currentNode;

      if(isNodeExisting(toVisit,&nodeMap[(currentNode->x+1)*MAP_SIZE +currentNode->y])){
        if(currentNode->g+1 > nodeMap[(currentNode->x+1)*MAP_SIZE +currentNode->y].g){

        }
        else{
          setNodeValues(&nodeMap[(currentNode->x+1)*MAP_SIZE +currentNode->y],*currentNode,*destNode);
          insertion(toVisit,&nodeMap[(currentNode->x+1)*MAP_SIZE +currentNode->y]);
        }
      }
      else{
          setNodeValues(&nodeMap[(currentNode->x+1)*MAP_SIZE +currentNode->y],*currentNode,*destNode);
          insertion(toVisit,&nodeMap[(currentNode->x+1)*MAP_SIZE +currentNode->y]);
      }
    }
    if(isValid(currentNode->x-1,currentNode->y, map) && !(isNodeExisting(visited,&nodeMap[(currentNode->x-1)*MAP_SIZE +currentNode->y]))){

      nodeMap[(currentNode->x-1)*MAP_SIZE +currentNode->y].parent = currentNode;

      if(isNodeExisting(toVisit,&nodeMap[(currentNode->x-1)*MAP_SIZE +currentNode->y])){
        if(currentNode->g+1 > nodeMap[(currentNode->x-1)*MAP_SIZE +currentNode->y].g){

        }
        else{
          setNodeValues(&nodeMap[(currentNode->x-1)*MAP_SIZE +currentNode->y],*currentNode,*destNode);
          insertion(toVisit,&nodeMap[(currentNode->x-1)*MAP_SIZE +currentNode->y]);
        }
      }
      else{
          setNodeValues(&nodeMap[(currentNode->x-1)*MAP_SIZE +currentNode->y],*currentNode,*destNode);
          insertion(toVisit,&nodeMap[(currentNode->x-1)*MAP_SIZE +currentNode->y]);
      }
    }
    if(isValid(currentNode->x,currentNode->y-1, map) && !(isNodeExisting(visited,&nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y-1)]))){

      nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y-1)].parent = currentNode;

      if(isNodeExisting(toVisit,&nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y-1)])){
        if(currentNode->g+1 > nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y-1)].g){

        }
        else{
          setNodeValues(&nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y-1)],*currentNode,*destNode);
          insertion(toVisit,&nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y-1)]);
        }
      }
      else{
          setNodeValues(&nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y-1)],*currentNode,*destNode);
          insertion(toVisit,&nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y-1)]);
      }
    }
    if(isValid(currentNode->x,currentNode->y+1, map) && !(isNodeExisting(visited,&nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y+1)]))){

      nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y+1)].parent = currentNode;

      if(isNodeExisting(toVisit,&nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y+1)])){
        if(currentNode->g+1 > nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y+1)].g){

        }
        else{
          setNodeValues(&nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y+1)],*currentNode,*destNode);
          insertion(toVisit,&nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y+1)]);
        }
      }
      else{
          setNodeValues(&nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y+1)],*currentNode,*destNode);
          insertion(toVisit,&nodeMap[(currentNode->x)*MAP_SIZE +(currentNode->y+1)]);
      }
    }

  }


  //If there is no path found we return an empty stack
  if(currentNode == NULL || (currentNode->x!=destNode->x && currentNode->y!=destNode->y)){
    return path;
  }

  //Else we fill in the path stack
  else{
    while (currentNode->parent != NULL) {
      //displayNode(*currentNode);
      PathCoordinates newPathCoord;
      newPathCoord.x = currentNode->x;
      newPathCoord.y = currentNode->y;
      path.push(newPathCoord);
      currentNode=currentNode->parent;
    }

    return path;
  }
  free(nodeMap);
}
