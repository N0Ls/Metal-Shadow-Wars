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
    // game->changeState(true);
    game = new Game();

    game->init("IMAC WARS 2 - Game", WINDOW_WIDTH, WINDOW_HEIGHT);

    game->selected_unit = nullptr;

    game->placeUnits();

    while (game->running())
    {
      frameStart = SDL_GetTicks();

      game->handleEvents();
      game->update();
      game->draw(game->surface);

      frameTime = SDL_GetTicks() - frameStart;

      while(game->paused())
      {
        menu = new Menu();
        menu->showPause(game->surface);
      }

      if (frameDelay > frameTime)
      {
        SDL_Delay(frameDelay - frameTime);
      }
    }

    game->clean();
  }

  return 0;
}
