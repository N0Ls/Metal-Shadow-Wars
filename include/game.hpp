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
#include "player.hpp"

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
    void draw(SDL_Surface *surface);
    bool running() { return isRunning; };
    void clickCheck(float mouseX,float mouseY);

    void changeState(bool state);

    int turn;

    static const int nb_players = 2 ;
    static const int nb_start_units = 3;
    player players[nb_players];

    //Textures
    static const int nb_sub_groups_textures = 2;
    static const int nb_textures_map = 6;
    static const int nb_textures_units = 1;

    GLuint textureIds_map[nb_textures_map];
    GLuint textureLink[MAP_SIZE*2];
    GLuint textureIds_units[nb_textures_units];

    int tabMap[MAP_SIZE * MAP_SIZE];

    unit *selected_unit=NULL;
    player *currentPlayer=NULL;

    bool move = false;
    bool moving_unit = false;

    bool unitPlaced=false;
    void placeUnits();

    bool validClickMove(int x, int y);
    bool validClickAttack(int x, int y);

    void nextTurn();
    void autoPlayer();

private :
    int counter;
    bool isRunning;
    Mix_Music *music = NULL;
    Mix_Chunk *click = NULL;
    int lastClickX;
    int lastClickY;

    int currentTurn;

    void displaySelectdUnit();
    player* getCurrentPlayer();
};

#endif /* GAME_H */
