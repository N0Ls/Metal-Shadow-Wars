#ifndef NODE_H
#define NODE_H

typedef struct {
  int x,y;
  double heuristic, g_cost, f_weight;
} Node;

#endif
