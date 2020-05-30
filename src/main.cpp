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
#include "ui.hpp"

#include <iostream>

Menu *menu = nullptr;
Game *game = nullptr;

int main(int argc, const char *argv[])
{
  const int FPS = 60;
  const int frameDelay = 1000 / FPS;

  Uint32 frameStart;
  int frameTime;

  menu = new Menu();
  int c = menu->showMain("IMAC WARS 2 - Menu", WINDOW_WIDTH, WINDOW_HEIGHT);

  if (c == 0)
  {
    game = new Game();

    game->init("METAL SHADOW WARS - Game", WINDOW_WIDTH, WINDOW_HEIGHT);

    game->selected_unit = nullptr;

    game->placeUnits();

    while (game->running())
    {
      frameStart = SDL_GetTicks();

      game->handleEvents();

      game->draw();
      game->update();

      frameTime = SDL_GetTicks() - frameStart;


      if (frameDelay > frameTime)
      {
        SDL_Delay(frameDelay - frameTime);
      }
    }
    loadEndMenu(&game->endMenuSurface[0], game->textureEndMenu, game->currentPlayer);
    while(game->endMenu){
      game->handleEvents();
      displayEndMenu(&game->endMenuSurface[0], game->textureEndMenu);
    }
    game->clean();
  }

  return 0;
}
