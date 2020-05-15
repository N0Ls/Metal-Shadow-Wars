#ifndef MENU_H
#define MENU_H

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

static const unsigned int NUMMENU = 2;

class Menu
{

public :
    Menu();
    ~Menu();
    SDL_Surface *surface;
    int show(const char* title, int width, int height);
    bool running() { return isActiv; };

private :
    bool isActiv;
    const char *labels[NUMMENU] = {"Play", "Exit"};
    SDL_Color color[2] = {{255, 255, 255}, {255, 0, 0}};

};

#endif