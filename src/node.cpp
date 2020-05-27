#include "constants.hpp"
#include "node.hpp"
#include <stdlib.h>
#include <limits>
using namespace std;
#include <iostream>
#include <stack>

void initNode(Node *node, int x, int y)
{
  node->x=x;
  node->y=y;
}
void setValidity(Node *node, bool validity)
{
  node->validity=validity;
}

void displayNode(Node node){
  std::cout << node.x<< " , " << node.y << " is valid : " << node.validity <<'\n';
}

bool isValid(int x, int y, int map[MAP_SIZE*MAP_SIZE])
{
    if((x>=0 && y>=0 && x<MAP_SIZE && y<MAP_SIZE) && (map[(x)*MAP_SIZE+ y]==1 || map[(x)*MAP_SIZE+ y]==2)){
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

void insertion(Liste *liste, Node *nvNode)
{
    /* Création du nouvel élément */
    Element *nouveau = (Element *) malloc(sizeof(Element *));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->node = nvNode;

     nouveau->next = liste->first;
     liste->first = nouveau;
}

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

void setNodeValues(Node *nodeToSet, Node current,Node dest){
  nodeToSet->g = (current.g)+1;
  nodeToSet->h = calculateHeuristic(nodeToSet->x, nodeToSet->y,dest);
  nodeToSet->f=nodeToSet->g+nodeToSet->h;
}

std::stack <PathCoordinates> aStar(int map[MAP_SIZE*MAP_SIZE], int xStart, int yStart, int xDest, int yDest){
  Node nodeMap[MAP_SIZE*MAP_SIZE];
  stack <PathCoordinates> path;
  //le tableau de pointeur est surement inutile

  for (int j = 0; j < MAP_SIZE; j++) {
    for (int k = 0; k < MAP_SIZE; k++) {
      initNode(&nodeMap[j*MAP_SIZE +k],j,k);
      setValidity(&nodeMap[j*MAP_SIZE +k],map[j*MAP_SIZE+k]);
    }
  }

  Node *startingNode = &nodeMap[xStart*MAP_SIZE +yStart];
  Node *destNode = &nodeMap[xDest*MAP_SIZE +yDest];

  Node *currentNode = startingNode;

  // displayNode(*startingNode);
  // displayNode(*destNode);

  if(destNode->validity == false){
    std::cout << "case non valide" << '\n';
    return path;
  }

  Liste *visited = (Liste *) malloc(sizeof(Liste *));
  Liste *toVisit = (Liste *) malloc(sizeof(Liste *));


  if (visited == NULL || toVisit == NULL ){exit(EXIT_FAILURE);}

  Element *elementStart = (Element *) malloc(sizeof(Element *));

  startingNode->f=0;
  startingNode->parent =NULL;
  elementStart->node = startingNode;
  elementStart->next = NULL;

  toVisit->first = NULL;
  visited->first = elementStart;


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


  bool found = 0;
  while(found==0 && toVisit->first !=NULL){

    currentNode = findcheapestNode(toVisit);
    //cout <<"cheapestNode : " ;
    //displayNode(*currentNode);
    deleteNode(toVisit,*currentNode);
    insertion(visited,currentNode);

    // afficherListe(visited);
    // afficherListe(toVisit);

    if(currentNode->x == destNode->x && currentNode->y == destNode->y){
      cout<<"trouvé" << endl;
      found=1;
    }

    else{
      //cout << "pas encore trouvé"<<endl;
    }

    //check pour chaque enfant
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
//function to generate the tab of nodes
