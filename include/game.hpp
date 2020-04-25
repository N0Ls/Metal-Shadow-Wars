#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

class Game
{

public :
    Game();
    ~Game();

    void init(const char* title, int width, int height);

    void handleEvents();
    void update();
    void clean();
    void draw();
    bool running() { return isRunning; };

private :
    int counter;
    bool isRunning;
    SDL_Surface *surface;

};

#endif /* GAME_H */
