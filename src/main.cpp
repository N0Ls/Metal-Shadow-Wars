#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <SDL/SDL_ttf.h>

#include "game.hpp"
#include "constants.hpp"
#include "texture.hpp"
#include "player.hpp"
#include "unit.hpp"
#include "node.hpp"
#include "map.hpp"
#include "menu.hpp"
#include <string.h>

#include <iostream>

Game *game = nullptr;

int main(int argc, const char *argv[])
{
  game = new Game();

  game->init("IMAC WARS 2", WINDOW_WIDTH, WINDOW_HEIGHT);

  //init_textures(game->nb_textures_map, game->textureIds_map,game->textureLink);
  //printf("%d\n",game->textureLink[MAP_SIZE -17]); //Test pour voir si le tableau était rempli en sortie

  player newPlayer;
  initPlayer(&newPlayer, 1, 3);
  std::cout << newPlayer.resources << std::endl;

  setCoordinates(game->players->units, 3, 2);
  printUnitInfos(game->players->units);
  updateDisplayCoordinates(game->players->units);

  //game->selected_unit = game->players->units;
  // int maze[MAP_SIZE][MAP_SIZE] = {
  //   {1,1,1,1,0,0,1,1,1,1},
  //   {0,0,1,0,0,0,1,1,1,1},
  //   {0,1,1,1,1,1,1,1,1,1},
  //   {1,1,1,1,1,1,1,1,1,1},
  //   {1,1,1,1,1,1,1,1,1,1},
  //   {1,1,1,1,1,1,1,1,1,1},
  //   {1,1,1,1,1,1,1,1,1,1},
  //   {1,1,1,1,1,1,1,1,1,1},
  //   {1,1,1,1,1,1,1,1,1,1},
  //   {1,1,1,1,1,1,1,1,1,1},
  // };
  int maze[MAP_SIZE * MAP_SIZE] =
      {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  int maze2[MAP_SIZE * MAP_SIZE];
  loadMap(maze2);
  //aStar(maze,5,4,0,0);

  // SDL_Surface *screen;
  // const int width = 640;
  // const int height = 480;
  // const int FPS = 30;
  // screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
  // TTF_Font *font;
  // TTF_Init();
  // font = TTF_OpenFont("Test.ttf", 30);
  // SDL_Color color = {0, 0, 0};
  // SDL_Event event;
  // Uint32 start;
  // bool arr[4] = {0, 0, 0, 0};
  
  // int i = show_menu(screen);

  // // En fonction de la valeur retournée, on change l'état du jeu

  // if (i == 1)
  //   game->isRunning = false;

  while (game->running())
  {
    game->handleEvents();
    game->update();
    game->draw(game->surface, maze2);
    //displayUnit(&unit_test,game->textureIds_units);
  }

  game->clean();
  return 0;
}
