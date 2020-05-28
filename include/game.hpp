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
#include "map.hpp"
#include "menu.hpp"
#include "text.hpp"

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
    void draw();
    bool running() { return isRunning; };
    bool paused() { return isPaused; };
    bool done() { return isDone; };
    void clickCheck(float mouseX,float mouseY);

    void changeState(bool state);

    int turn;

    static const int nb_players = 2 ;
    static const int nb_start_units = 5;
    player players[nb_players];

    //Textures
    static const int nb_sub_groups_textures = 2;
    static const int nb_textures_map = 4;
    static const int nb_textures_units = 3;
    static const int nb_textures_txt = 1;

    GLuint textureIds_map[nb_textures_map];
    GLuint textureLink[MAP_SIZE*2];
    GLuint textureIds_units[nb_textures_units];
    GLuint menu_tex[1];
    GLuint textureText[nb_textures_txt];
    SDL_Surface surfaceTextes[nb_textures_txt];

    //int tabMap[MAP_SIZE * MAP_SIZE];
    TileMap tabMapTile[MAP_SIZE * MAP_SIZE];

    Unit *selected_unit=NULL;
    player *currentPlayer=NULL;

    bool move = false;
    bool moving_unit = false;

    bool unitPlaced=false;
    void placeUnits();

    bool validClickMove(int x, int y);
    bool validClickAttack(int x, int y);

    void nextTurn();
    void autoPlayer();

    std::vector<Unit*> unitRef;

    SDL_Surface *pause;
private :
    int counter;
    bool isRunning;
    bool isPaused;
    bool isDone;
    Mix_Music *music = NULL;
    Mix_Chunk *click = NULL;
    int lastClickX;
    int lastClickY;

    int currentTurn;

    void updateUnitList();
    void displaySelectdUnit();
    player* getCurrentPlayer();

};

#endif /* GAME_H */
