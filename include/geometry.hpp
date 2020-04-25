#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>


static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;

static const unsigned int STEP_W = 80;
static const unsigned int STEP_H = 60;

static const unsigned int w = WINDOW_WIDTH/STEP_W;
static const unsigned int h = WINDOW_HEIGHT/STEP_H;


void fillGrid();
void drawSquare(int i, int j);

#endif
