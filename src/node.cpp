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
    if((x>=0 && y>=0 && x<MAP_SIZE && y<MAP_SIZE) && (map[(x)*MAP_SIZE+ y]==1 || map[(x)*MAP_SIZE+ y]==2 || map[(x)*MAP_SIZE+ y]==3)){
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

// int maze[MAP_SIZE][MAP_SIZE] = {
//   {1,1,1,1,1,1,1,1,1,1},
//   {1,1,1,1,1,1,1,1,1,1},
//   {1,1,1,1,1,1,1,1,1,1},
//   {1,1,1,1,1,1,1,1,1,1},
//   {1,1,1,1,1,1,1,1,1,1},
//   {1,1,1,1,1,1,1,1,1,1},
//   {1,1,1,1,1,1,1,1,1,1},
//   {1,1,1,1,1,1,1,1,1,1},
//   {1,1,1,1,1,1,1,1,1,1},
//   {1,1,1,1,1,1,1,1,1,1},
// };

// void generateNodeTab(int map[][MAP_SIZE], Node nodeMap[]){
//   for (int j = 0; j < MAP_SIZE; j++) {
//     for (int k = 0; k < MAP_SIZE; k++) {
//       initNode(nodeMap[j*MAP_SIZE +k],j,k);
//     }
//   }
// }
// void insertion(Liste *liste, Node* nodeToAdd){
//     Element *newElement = (Element *) malloc(sizeof(Element *));
//     if (liste==NULL || newElement == NULL)
//     {
//         exit(EXIT_FAILURE);
//     }
//
//     newElement->node = nodeToAdd;
//     newElement->next = NULL;
//
//     if(liste->first == NULL){
//       liste->first = newElement;
//       return;
//     }
//
//     Element *tmp = liste->first;
//     while(tmp->next != NULL){
//       tmp = tmp->next;
//     }
//     tmp->next = newElement;
//
//     return;
// }

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
      displayNode(*current->node);
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
      //free(current);
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

Node * aStar(int map[MAP_SIZE*MAP_SIZE], int xStart, int yStart, int xDest, int yDest){
  Node nodeMap[MAP_SIZE*MAP_SIZE];

  //le tableau de pointeur est surement inutile
  Node** nodeMapPTR;
  nodeMapPTR =(Node**) malloc(MAP_SIZE*MAP_SIZE * sizeof(Node*));

  for (int j = 0; j < MAP_SIZE; j++) {
    for (int k = 0; k < MAP_SIZE; k++) {
      initNode(&nodeMap[j*MAP_SIZE +k],j,k);
      setValidity(&nodeMap[j*MAP_SIZE +k],map[j*MAP_SIZE+k]);
      nodeMapPTR[j*MAP_SIZE +k] = &nodeMap[j*MAP_SIZE +k];
    }
  }

  Node *startingNode = nodeMapPTR[xStart*MAP_SIZE +yStart];
  Node *destNode = &nodeMap[xDest*MAP_SIZE +yDest];

  Node *currentNode = startingNode;

  displayNode(*startingNode);
  displayNode(*destNode);

  if(destNode->validity == false){
    std::cout << "case non valide" << '\n';
    return(currentNode);
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

  //cout << "Le node y est : "<<isNodeExisting(visited,currentNode)<<endl;

  if(isValid(currentNode->x+1,currentNode->y,map) && !(isNodeExisting(visited,nodeMapPTR[(currentNode->x+1)*MAP_SIZE +currentNode->y]))){
    nodeMapPTR[(currentNode->x+1)*MAP_SIZE +currentNode->y]->parent = currentNode;
    setNodeValues(nodeMapPTR[(currentNode->x+1)*MAP_SIZE +currentNode->y],*currentNode,*destNode);
    insertion(toVisit,nodeMapPTR[(currentNode->x+1)*MAP_SIZE +currentNode->y]);
  }
  if(isValid(currentNode->x-1,currentNode->y,map) && !(isNodeExisting(visited,nodeMapPTR[(currentNode->x-1)*MAP_SIZE +currentNode->y]))){
    nodeMapPTR[(currentNode->x-1)*MAP_SIZE +currentNode->y]->parent = currentNode;
    setNodeValues(nodeMapPTR[(currentNode->x-1)*MAP_SIZE +currentNode->y],*currentNode,*destNode);
    insertion(toVisit,nodeMapPTR[(currentNode->x-1)*MAP_SIZE +currentNode->y]);
  }
  if(isValid(currentNode->x,currentNode->y-1,map) && !(isNodeExisting(visited,nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y-1)]))){
    nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y-1)]->parent = currentNode;
    setNodeValues(nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y-1)],*currentNode,*destNode);
    insertion(toVisit,nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y-1)]);
  }
  if(isValid(currentNode->x,currentNode->y+1,map)&& !(isNodeExisting(visited,nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y+1)]))){
    nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y+1)]->parent = currentNode;
    setNodeValues(nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y+1)],*currentNode,*destNode);
    insertion(toVisit,nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y+1)]);
  }


  // currentNode = findcheapestNode(toVisit);
  // cout <<"cheapestNode : " ;
  // displayNode(*currentNode);
  // deleteNode(toVisit,*currentNode);
  // afficherListe(toVisit);

  bool found = 0;
  // //future boucle while
  while(found==0 && toVisit->first !=NULL){

    currentNode = findcheapestNode(toVisit);
    cout <<"cheapestNode : " ;
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
      cout << "pas encore trouvé"<<endl;
    }

    //check pour chaque enfant
    if(isValid(currentNode->x+1,currentNode->y, map) && !(isNodeExisting(visited,nodeMapPTR[(currentNode->x+1)*MAP_SIZE +currentNode->y]))){

      nodeMapPTR[(currentNode->x+1)*MAP_SIZE +currentNode->y]->parent = currentNode;

      if(isNodeExisting(toVisit,nodeMapPTR[(currentNode->x+1)*MAP_SIZE +currentNode->y])){
        if(currentNode->g+1 > nodeMapPTR[(currentNode->x+1)*MAP_SIZE +currentNode->y]->g){

        }
        else{
          setNodeValues(nodeMapPTR[(currentNode->x+1)*MAP_SIZE +currentNode->y],*currentNode,*destNode);
          insertion(toVisit,nodeMapPTR[(currentNode->x+1)*MAP_SIZE +currentNode->y]);
        }
      }
      else{
          setNodeValues(nodeMapPTR[(currentNode->x+1)*MAP_SIZE +currentNode->y],*currentNode,*destNode);
          insertion(toVisit,nodeMapPTR[(currentNode->x+1)*MAP_SIZE +currentNode->y]);
      }
    }
    if(isValid(currentNode->x-1,currentNode->y, map) && !(isNodeExisting(visited,nodeMapPTR[(currentNode->x-1)*MAP_SIZE +currentNode->y]))){

      nodeMapPTR[(currentNode->x-1)*MAP_SIZE +currentNode->y]->parent = currentNode;

      if(isNodeExisting(toVisit,nodeMapPTR[(currentNode->x-1)*MAP_SIZE +currentNode->y])){
        if(currentNode->g+1 > nodeMapPTR[(currentNode->x-1)*MAP_SIZE +currentNode->y]->g){

        }
        else{
          setNodeValues(nodeMapPTR[(currentNode->x-1)*MAP_SIZE +currentNode->y],*currentNode,*destNode);
          insertion(toVisit,nodeMapPTR[(currentNode->x-1)*MAP_SIZE +currentNode->y]);
        }
      }
      else{
          setNodeValues(nodeMapPTR[(currentNode->x-1)*MAP_SIZE +currentNode->y],*currentNode,*destNode);
          insertion(toVisit,nodeMapPTR[(currentNode->x-1)*MAP_SIZE +currentNode->y]);
      }
    }
    if(isValid(currentNode->x,currentNode->y-1, map) && !(isNodeExisting(visited,nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y-1)]))){

      nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y-1)]->parent = currentNode;

      if(isNodeExisting(toVisit,nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y-1)])){
        if(currentNode->g+1 > nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y-1)]->g){

        }
        else{
          setNodeValues(nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y-1)],*currentNode,*destNode);
          insertion(toVisit,nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y-1)]);
        }
      }
      else{
          setNodeValues(nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y-1)],*currentNode,*destNode);
          insertion(toVisit,nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y-1)]);
      }
    }
    if(isValid(currentNode->x,currentNode->y+1, map) && !(isNodeExisting(visited,nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y+1)]))){

      nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y+1)]->parent = currentNode;

      if(isNodeExisting(toVisit,nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y+1)])){
        if(currentNode->g+1 > nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y+1)]->g){

        }
        else{
          setNodeValues(nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y+1)],*currentNode,*destNode);
          insertion(toVisit,nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y+1)]);
        }
      }
      else{
          setNodeValues(nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y+1)],*currentNode,*destNode);
          insertion(toVisit,nodeMapPTR[(currentNode->x)*MAP_SIZE +(currentNode->y+1)]);
      }
    }

  }
  displayNode(*currentNode);
  if(currentNode == NULL || (currentNode->x!=destNode->x && currentNode->y!=destNode->y)){
    return startingNode;
  }
  else{
    return currentNode;
      while (currentNode != NULL) {
        displayNode(*currentNode);
        currentNode=currentNode->parent;
      }
  }

  //   insertion(visited)

  // let the currentNode equal the node with the least f value
  // remove the currentNode from the openList
  // add the currentNode to the closedList



  //insertion(visited,startingNode);



  // while (currentNode->x != xDest && currentNode->y != yDest) {
  //
  //
  // }




  free(nodeMapPTR);
}
//function to generate the tab of nodes
