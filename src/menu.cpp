#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <menu.hpp>
#include <iostream>
#include "texture.hpp"
#include "constants.hpp"

static const unsigned int BIT_PER_PIXEL = 32;

Menu::Menu() {}

Menu::~Menu() {}

void drawQuadsBG(){
  glBegin(GL_QUADS);
    glColor3f(1,1,1);
      glTexCoord2f(0 ,0);
      glVertex2f(0,0);

      glTexCoord2f(1 ,0);
      glVertex2f(MAP_TILE_SIZE,0);

      glTexCoord2f( 1 , 1);
      glVertex2f(MAP_TILE_SIZE,MAP_TILE_SIZE);

      glTexCoord2f( 0 , 1);
      glVertex2f(0,MAP_TILE_SIZE);
  glEnd();
}

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

  font = TTF_OpenFont("./assets/fonts/Road_Rage.ttf", 40);

  // Menu buttons
  SDL_Surface *menus[NUMMENU];

  // Menu items font
  menus[0] = TTF_RenderText_Solid(font, mainLabels[0], color[0]);
  menus[1] = TTF_RenderText_Solid(font, mainLabels[1], color[0]);

  // Buttons rect (for positions)
  SDL_Rect pos[NUMMENU];

  // Buttons actual positions (x and y coordinates)
  pos[0].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
  pos[0].y = screen->clip_rect.h - 250;
  pos[1].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
  pos[1].y = screen->clip_rect.h - 150;

  // Selection state
  bool selected[NUMMENU] = {0, 0};

  SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

  //Init audio
  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
  {
    exit(EXIT_FAILURE);
  }

  //Loading music
  this->music = Mix_LoadMUS("./assets/sounds/menu.mp3");
  if (this->music == NULL )
  {
    fprintf(
        stderr,
        "Impossible de charger la musique.\n");
    exit(EXIT_FAILURE);
  }

  //Loading BG and LOGO
  char BG_path[255]={ "assets/background.jpg"};
  SDL_Surface *surfaceBG = IMG_Load(BG_path);

  char LOGO_path[255]={ "assets/logo-metal-shadow-wars-medium.png"};
  SDL_Surface *surfaceLOGO = IMG_Load(LOGO_path);

  //Play Music
  Mix_PlayMusic(this->music, -1);

  SDL_Event event;
  while (1)
  {
    if (Mix_PlayingMusic() == 0)
    {
      //On lance la musique | We start playing music
      Mix_PlayMusic(this->music, -1);
    }
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
    // glPushMatrix();
    // glScalef(1,-1,1.);
    // glBindTexture(GL_TEXTURE_2D, *this->textureBG);
    // drawQuadsBG();
    // glPopMatrix();
    // glBindTexture(GL_TEXTURE_2D, 0);
    SDL_Rect posBG;
    posBG.h = screen->w;;
    posBG.w = screen->w;
    posBG.x = 0;
    posBG.y = 0;
    SDL_BlitSurface(surfaceBG,&posBG, screen,&posBG);

    SDL_Rect posLOGO;
    posLOGO.h = surfaceLOGO->h;
    posLOGO.w = surfaceLOGO->w;
    posLOGO.x = screen->w/2- surfaceLOGO->w/2;
    posLOGO.y = 50;
    SDL_BlitSurface(surfaceLOGO,NULL, screen,&posLOGO);

    for (int i = 0; i <(int) NUMMENU; i += 1)
    {
      SDL_BlitSurface(menus[i], NULL, screen, &pos[i]);
    }
    SDL_Flip(screen);
    if (1000 / 30 > (SDL_GetTicks() - time))
      SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
  }
}
