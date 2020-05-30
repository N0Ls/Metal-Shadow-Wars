#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <SDL/SDL_ttf.h>

#include <menu.hpp>

#include <iostream>

static const unsigned int BIT_PER_PIXEL = 32;

Menu::Menu() {}

Menu::~Menu() {}

int Menu::showMain(const char *title, int width, int height)
{
  /* Initialisation de la SDL */
  if (-1 == SDL_Init(SDL_INIT_VIDEO))
  {
    isActiv = false;
    fprintf(
        stderr,
        "Impossible d'initialiser la SDL. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  else
  {
    fprintf(
        stderr,
        "SDL initialisée.\n");
  }

  SDL_Surface *screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);

  if (NULL == screen)
  {
    isActiv = false;
    fprintf(
        stderr,
        "Impossible d'ouvrir la fenêtre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  else
  {
    fprintf(
        stderr,
        "Menu initialisé.\n");
    isActiv = true;
  }

  Uint32 time;

  // Axes
  int x, y;

  // Font initialization
  TTF_Font *font;
  TTF_Init();

  font = TTF_OpenFont("./fonts/indelible.ttf", 40);

  // Menu buttons
  SDL_Surface *menus[NUMMENU];

  // Menu items font
  menus[0] = TTF_RenderText_Solid(font, mainLabels[0], color[0]);
  menus[1] = TTF_RenderText_Solid(font, mainLabels[1], color[0]);

  // Buttons rect (for positions)
  SDL_Rect pos[NUMMENU];

  // Buttons actual positions (x and y coordinates)
  pos[0].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
  pos[0].y = screen->clip_rect.h / 2 - menus[0]->clip_rect.h;
  pos[1].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
  pos[1].y = screen->clip_rect.h / 2 + menus[0]->clip_rect.h;

  // Selection state
  bool selected[NUMMENU] = {0, 0};

  SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

  SDL_Event event;
  while (1)
  {
    time = SDL_GetTicks();
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        SDL_FreeSurface(menus[0]);
        SDL_FreeSurface(menus[1]);
        return 1;
      case SDL_MOUSEMOTION:
        x = event.motion.x;
        y = event.motion.y;
        for (int i = 0; i <(int) NUMMENU; i += 1)
        {
          if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
          {
            if (!selected[i])
            {
              selected[i] = 1;
              SDL_FreeSurface(menus[i]);
              menus[i] = TTF_RenderText_Solid(font, mainLabels[i], color[1]);
            }
          }
          else
          {
            if (selected[i])
            {
              selected[i] = 0;
              SDL_FreeSurface(menus[i]);
              menus[i] = TTF_RenderText_Solid(font, mainLabels[i], color[0]);
            }
          }
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        x = event.button.x;
        y = event.button.y;
        for (int i = 0; i < (int)NUMMENU; i += 1)
        {
          if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
          {
            SDL_FreeSurface(menus[0]);
            SDL_FreeSurface(menus[1]);
            return i;
          }
        }
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
          SDL_FreeSurface(menus[0]);
          SDL_FreeSurface(menus[1]);
          return 0;
        }
      }
    }
    for (int i = 0; i <(int) NUMMENU; i += 1)
    {
      SDL_BlitSurface(menus[i], NULL, screen, &pos[i]);
    }
    SDL_Flip(screen);
    if (1000 / 30 > (SDL_GetTicks() - time))
      SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
  }
}
