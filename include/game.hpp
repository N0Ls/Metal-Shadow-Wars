#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "constants.hpp"
#include <SDL/SDL_mixer.h>
#include "unit.hpp"

class Game
{

public :
    Game();
    ~Game();
    SDL_Surface *surface;
    void reshape(SDL_Surface** surface, unsigned int width, unsigned int height);
    void init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void clean();
    void draw(SDL_Surface *surface, unit *unit);
    bool running() { return isRunning; };

    //Textures
    static const int nb_sub_groups_textures = 2;
    static const int nb_textures_map = 6;
    static const int nb_textures_units = 1;

    GLuint textureIds_map[nb_textures_map];
    GLuint textureLink[MAP_SIZE*2];
    GLuint textureIds_units[nb_textures_units];

    unit *selected_unit;

    int move = 0;


private :
    int counter;
    bool isRunning;
    Mix_Music *music = NULL;
};

#endif /* GAME_H */
