#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <iostream>
#include "game.hpp"
#include "constants.hpp"
#include "texture.hpp"
#include "player.hpp"
#include "unit.hpp"
#include "node.hpp"
#include "map.hpp"
#include "menu.hpp"
#include "ui.hpp"

Menu *menu = nullptr;
Game *game = nullptr;

/* MAIN */
int main(int argc, const char *argv[])
{
  const int FPS = 60;
  const int frameDelay = 1000 / FPS;

  Uint32 frameStart;
  int frameTime;

  //Start Menu creation
  menu = new Menu();
  int c = menu->showMain("IMAC WARS 2 - Menu", WINDOW_WIDTH, WINDOW_HEIGHT);

  if (c == 0)
  {
    game = new Game();
    game->init("METAL SHADOW WARS - Game", WINDOW_WIDTH, WINDOW_HEIGHT);

    //Game loop
    while (game->running())
    {
      frameStart = SDL_GetTicks();

      //Game methods call
      game->handleEvents();
      game->draw();
      game->update();

      frameTime = SDL_GetTicks() - frameStart;
      if (frameDelay > frameTime)
      {
        SDL_Delay(frameDelay - frameTime);
      }
    }

    //Ending screen
    loadEndMenu(&game->endMenuSurface[0], game->textureEndMenu, game->currentPlayer);
    while(game->endMenu){
      game->handleEvents();
      displayEndMenu(&game->endMenuSurface[0], game->textureEndMenu);
    }

    //Call game cleaning
    game->clean();
  }
  return 0;
}
