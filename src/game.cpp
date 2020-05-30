#include "game.hpp"
#include "map.hpp"
#include "constants.hpp"
#include "texture.hpp"
#include <iostream>
#include <SDL/SDL_mixer.h>
#include "player.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "node.hpp"
#include "text.hpp"
#include "ui.hpp"
#include <stack>
#include <vector>
#include <SDL/SDL_ttf.h>
using namespace std;

static const unsigned int BIT_PER_PIXEL = 32;

Game::Game()
{
}

Game::~Game()
{
}

void Game::reshape(SDL_Surface **surface, unsigned int width, unsigned int height)
{

  static float aspectRatio;
  SDL_Surface *surface_temp = SDL_SetVideoMode(
      width, height, BIT_PER_PIXEL,
      SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);
  if (NULL == surface_temp)
  {
    fprintf(
        stderr,
        "Erreur lors du redimensionnement de la fenetre.\n");
    exit(EXIT_FAILURE);
  }
  *surface = surface_temp;

  aspectRatio = width / (float)height;

  glViewport(0, 0, (*surface)->w, (*surface)->h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (aspectRatio > 1)
  {
    gluOrtho2D(
        -GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio,
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
  }
  else
  {
    gluOrtho2D(
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
        -GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
  }
}

void Game::init(const char *title, int width, int height)
{
  /* Initialisation de la SDL */
  if (-1 == SDL_Init(SDL_INIT_VIDEO))
  {
    isRunning = false;
    fprintf(
        stderr,
        "Impossible d'initialiser la SDL. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }

  /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
  surface = SDL_SetVideoMode(
      width, height, BIT_PER_PIXEL,
      SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);

  if (NULL == surface)
  {
    isRunning = false;
    fprintf(
        stderr,
        "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  else
  {
    isRunning = true;
  }

  isPaused = false;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);

  init_textures(this->nb_sub_groups_textures, this->nb_textures_map, this->nb_textures_units, this->textureIds_map, this->textureIds_units, this->textureLink);

  /* INIT PLAYERS */
  SDL_Color couleurJ1 = {.r = 255, .g = 0, .b = 0};
  SDL_Color couleurJ2 = {.r = 0, .g = 255, .b = 255};
  const char *name1 = "Michel";
  initPlayer(&this->players[0], 0, this->nb_start_units, name1, couleurJ1);
  initPlayer(&this->players[1], 1, this->nb_start_units, "Jacques", couleurJ2);

  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
  {
    exit(EXIT_FAILURE);
  }

  this->music = Mix_LoadMUS("sounds/game.mp3");
  this->click = Mix_LoadWAV("sounds/click.wav");

  if (this->music == NULL || this->click == NULL)
  {
    fprintf(
        stderr,
        "Impossible de charger la musique.\n");
    exit(EXIT_FAILURE);
  }
  Mix_PlayMusic(this->music, -1);

  loadMap(this->tabMapTile);
  loadPauseMenu(this->surfaceTextes,this->textureText);

  this->placeUnits();

  //Initialisation des tours
  this->turn = 1;
  this->currentPlayer = this->getCurrentPlayer();
  std::cout << "Tour n°" << Game::turn << endl;
  std::cout << "Joueur : " << this->currentPlayer->name << ", avec les unités :" << endl;

  reshape(&surface, width, height);
}

void Game::placeUnits()
{
  //Checking availableTiles
  vector<PathCoordinates> availableTiles;
  for (int j = 0; j < MAP_SIZE; j++)
  {
    for (int k = 0; k < MAP_SIZE; k++)
    {
      if (this->tabMapTile[j * MAP_SIZE + k].isWalkable)
      {
        PathCoordinates newTile;
        newTile.x = j;
        newTile.y = k;
        availableTiles.push_back(newTile);
      }
    }
  }

  //Displaying availableTiles
  // for(int a=0; a<(int)availableTiles.size(); a++){
  //   cout << availableTiles[a].x << " : " << availableTiles[a].y << endl;
  // }

  //Placing Units
  for (int i = 0; i < this->nb_players; i++)
  {
    for (int y = 0; y < this->players[i].nbUnits; y++)
    {
      srand(time(NULL) + rand());
      //Maybe add different range for each players
      int randIndex = rand() % availableTiles.size();
      PathCoordinates randomTile = availableTiles[randIndex];
      availableTiles.erase(availableTiles.begin() + randIndex); //removing available tile after use
      setCoordinates(&this->players[i].units[y], randomTile.x, randomTile.y);
      this->players[i].units[y].displayX = (-GL_VIEW_SIZE / 2) + this->players[i].units[y].x * MAP_TILE_SIZE;
      this->players[i].units[y].displayY = (-GL_VIEW_SIZE / 2) + this->players[i].units[y].y * MAP_TILE_SIZE;
    }
  }

  this->updateUnitList();
  this->unitPlaced = true;
}

void Game::handleEvents()
{
  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    /* Close window */
    if (e.type == SDL_QUIT)
    {
      isRunning = false;
      endMenu = false;
      break;
    }

    /* Close window | Fermer la fenêtre */
    if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
    {
      isRunning = false;
      endMenu = false;
      break;
    }

    /* Pause state | Etat de pause*/
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
    {
      //isPaused == true ? isPaused = false : isPaused = true;
      if (this->isPaused == true)
      {
        this->isPaused = false;
        Mix_ResumeMusic();
      }
      else
      {
        this->isPaused = true;
        cout << "game paused " << endl;
        Mix_PauseMusic();
      }
      //std::cout << isPaused << std::endl;
    }

    if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_m))
    {
      if (Mix_PlayingMusic() == 0)
      {
        //On lance la musique | We start playing music
        Mix_PlayMusic(this->music, -1);
        break;
      }
      else
      {
        //Si la musique est en pause
        if (Mix_PausedMusic() == 1)
        {
          //On enlève la pause (la musique repart où elle en était)
          Mix_ResumeMusic();
          break;
        }
        //Si la musique est en train de jouer
        else
        {
          //On met en pause la musique
          Mix_PauseMusic();
          break;
        }
      }
    }

    switch (e.type)
    {
    /* Clic souris */
    case SDL_MOUSEBUTTONUP:
      break;
    case SDL_MOUSEBUTTONDOWN:
      if (e.button.button == SDL_BUTTON_LEFT)
      {
        //printf("clic en (%d, %d)\n", e.button.x, e.button.y);
        Mix_PlayChannel(-1, this->click, 0);
        if (this->currentPlayer != NULL && this->currentPlayer->id == 1 && this->isPaused==false)
        {
          this->clickCheck(e.button.x, e.button.y);
        }
      }
      break;

    /* Mouvement souris */
    case SDL_MOUSEMOTION:
      //printf("souris en (%d, %d)\n", e.button.x, e.button.y);
      break;

    /* Touche clavier */
    case SDL_KEYDOWN:
      printf("touche pressee (code = %d)\n", e.key.keysym.sym);
      if (e.key.keysym.sym == 275 || e.type == SDLK_RIGHT)
      {
        std::cout << "Call nextTurn" << std::endl;
        nextTurn();
      }
      break;
    case SDL_VIDEORESIZE:
      reshape(&surface, e.resize.w, e.resize.h);
      break;
    default:
      break;
    }
  }
}

void drawQuadsSelection()
{
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex2f(0, 0);

  glTexCoord2f(1, 0);
  glVertex2f(MAP_TILE_SIZE, 0);

  glTexCoord2f(1, 1);
  glVertex2f(MAP_TILE_SIZE, MAP_TILE_SIZE);

  glTexCoord2f(0, 1);
  glVertex2f(0, MAP_TILE_SIZE);
  glEnd();
}

void Game::draw()
{
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  fillGrid(this->textureIds_map, this->textureLink, this->tabMapTile);
  this->displaySelectdUnit();
  for (int g = 0; g < this->nb_players; g++)
  {
    for (int a = 0; a < this->players[g].nbUnits; a++)
    {
      if (this->players[g].units[a].isAlive == true)
      {
        displayUnit(&this->players[g].units[a], this->textureIds_units);
      }
    }
  }

  if (this->isPaused)
  {
    displayPauseMenu(this->surfaceTextes , this->textureText);
  }
  SDL_GL_SwapBuffers();
}



void Game::update()
{
  //Checking victory
  for (int y = 0; y < this->nb_players; y++)
  {
    if (this->players[y].nbUnits <= 0 || players[y].isAlive == false)
    {
      this->isRunning = false;
      this->endMenu = true;
      return;
    }
  }

  if (this->currentPlayer != NULL && this->currentPlayer->id == 0)
  {
    this->autoPlayer();
  }

  //Checking units status
  bool playerDone = true;
  for (int i = 0; i < this->currentPlayer->nbUnits; i++)
  {
    if (this->currentPlayer->units[i].isDONE == false)
    {
      playerDone = false;
    }
  }
  if (playerDone)
  {
    nextTurn();
  }
  return;
}

void Game::autoPlayer()
{
  for (int i = 0; i < this->currentPlayer->nbUnits; i++)
  {
    this->updateUnitList();
    if (this->currentPlayer->units[i].isDONE == false)
    {
      if (this->currentPlayer->units[i].isMoving == false)
      {
        autoMove(&currentPlayer->units[i], this->tabMapTile, this->unitRef);
      }
      else if (this->currentPlayer->units[i].hasToAttack == true)
      {
        autoAttack(&currentPlayer->units[i], this->tabMapTile, this->unitRef);
      }
    }
  }
}

void Game::updateUnitList()
{
  unitRef.clear();
  for (int i = 0; i < this->nb_players; i++)
  {
    for (int y = 0; y < this->players[i].nbUnits; y++)
    {
      this->unitRef.push_back(&this->players[i].units[y]);
    }
  }
}

player *Game::getCurrentPlayer()
{
  return &this->players[this->turn % this->nb_players];
}

void Game::nextTurn()
{
  //end of last turn
  this->updateUnitList();
  //reset last current player units status
  for (int u = 0; u < this->currentPlayer->nbUnits; u++)
  {
    Unit *unitToReset;
    unitToReset = &this->currentPlayer->units[u];
    updateTextUnit(unitToReset);
    unitToReset->isDONE = false;
  }

  //increment tour
  this->turn++;

  this->currentPlayer = this->getCurrentPlayer();
  this->selected_unit = nullptr;
  std::cout << "Tour n°" << Game::turn << endl;
  //std::cout << "Joueur : " << currentPlayer.name << ", avec les unités :" << endl;
  // for (int i = 0; i < this->currentPlayer->nbUnits; i++)
  // {
  //   printUnitInfos(&currentPlayer->units[i]);
  // }
  //
  // for(int y=0; y<this->nb_players ; y++){
  //   isAlive(&this->players[y]);
  // }
  // if(this->players[0].isAlive == false || this->players[1].isAlive==false){
  //   this->isRunning=false;
  // }
}

void displayPyramid(Unit unit, int size, TileMap tabMap[])
{
  glPushMatrix();
  glScalef(1, -1, 1.);
  //Drawing red square on selected unit
  glPushMatrix();
  glTranslatef(unit.displayX, unit.displayY, 0);
  drawQuadsSelection();
  glPopMatrix();

  for (int y = 0; y <= size; y++)
  {
    for (int j = 0; j <= size - y; j++)
    {
      glPushMatrix();
      glTranslatef((-GL_VIEW_SIZE / 2) + (unit.x + y) * MAP_TILE_SIZE, (-GL_VIEW_SIZE / 2) + (unit.y + j) * MAP_TILE_SIZE, 0);
      if (!(unit.x + y >= MAP_SIZE || unit.y + j >= MAP_SIZE) && (tabMap[(unit.x + y) * MAP_SIZE + unit.y + j].isWalkable))
        drawQuadsSelection();
      glPopMatrix();
      glPushMatrix();
      glTranslatef((-GL_VIEW_SIZE / 2) + (unit.x - y) * MAP_TILE_SIZE, (-GL_VIEW_SIZE / 2) + (unit.y - j) * MAP_TILE_SIZE, 0);
      if (!(unit.x - y < 0 || unit.y - j < 0) && (tabMap[(unit.x - y) * MAP_SIZE + unit.y - j].isWalkable))
        drawQuadsSelection();
      glPopMatrix();
      glPushMatrix();
      glTranslatef((-GL_VIEW_SIZE / 2) + (unit.x + y) * MAP_TILE_SIZE, (-GL_VIEW_SIZE / 2) + (unit.y - j) * MAP_TILE_SIZE, 0);
      if (!(unit.x + y >= MAP_SIZE || unit.y - j < 0) && (tabMap[(unit.x + y) * MAP_SIZE + unit.y - j].isWalkable))
        drawQuadsSelection();
      glPopMatrix();
      glPushMatrix();
      glTranslatef((-GL_VIEW_SIZE / 2) + (unit.x - y) * MAP_TILE_SIZE, (-GL_VIEW_SIZE / 2) + (unit.y + j) * MAP_TILE_SIZE, 0);
      if (!(unit.x - y < 0 || unit.y + j >= MAP_SIZE) && (tabMap[(unit.x - y) * MAP_SIZE + unit.y + j].isWalkable))
        drawQuadsSelection();
      glPopMatrix();
    }
  }
  glPopMatrix();
}

void displayDestroyPyramid(Unit unit, int size, TileMap tabMap[]){
  glPushMatrix();
  glScalef(1, -1, 1.);


  for (int y = 0; y <= size; y++)
  {
    for (int j = 0; j <= size - y; j++)
    {
      glPushMatrix();
      glTranslatef((-GL_VIEW_SIZE / 2) + (unit.x + y) * MAP_TILE_SIZE, (-GL_VIEW_SIZE / 2) + (unit.y + j) * MAP_TILE_SIZE, 0);
      if (!(unit.x + y >= MAP_SIZE || unit.y + j >= MAP_SIZE) && (tabMap[(unit.x + y) * MAP_SIZE + unit.y + j].isDestructible))
        drawQuadsSelection();
      glPopMatrix();
      glPushMatrix();
      glTranslatef((-GL_VIEW_SIZE / 2) + (unit.x - y) * MAP_TILE_SIZE, (-GL_VIEW_SIZE / 2) + (unit.y - j) * MAP_TILE_SIZE, 0);
      if (!(unit.x - y < 0 || unit.y - j < 0) && (tabMap[(unit.x - y) * MAP_SIZE + unit.y - j].isDestructible))
        drawQuadsSelection();
      glPopMatrix();
      glPushMatrix();
      glTranslatef((-GL_VIEW_SIZE / 2) + (unit.x + y) * MAP_TILE_SIZE, (-GL_VIEW_SIZE / 2) + (unit.y - j) * MAP_TILE_SIZE, 0);
      if (!(unit.x + y >= MAP_SIZE || unit.y - j < 0) && (tabMap[(unit.x + y) * MAP_SIZE + unit.y - j].isDestructible))
        drawQuadsSelection();
      glPopMatrix();
      glPushMatrix();
      glTranslatef((-GL_VIEW_SIZE / 2) + (unit.x - y) * MAP_TILE_SIZE, (-GL_VIEW_SIZE / 2) + (unit.y + j) * MAP_TILE_SIZE, 0);
      if (!(unit.x - y < 0 || unit.y + j >= MAP_SIZE) && (tabMap[(unit.x - y) * MAP_SIZE + unit.y + j].isDestructible))
        drawQuadsSelection();
      glPopMatrix();
    }
  }
  glPopMatrix();
}
void Game::displaySelectdUnit()
{
  if (this->selected_unit != NULL && this->selected_unit->isMoving == false && this->selected_unit->hasToAttack == false)
  {
    glColor4f(1, 0.6, 0, 0.5); //orange color
    displayPyramid(*this->selected_unit, this->selected_unit->dexterity, this->tabMapTile);
  }
  if (this->selected_unit != NULL && this->selected_unit->isMoving == false && this->selected_unit->hasToAttack == true)
  {
    glColor4f(0, 0.6, 1, 0.5); //light blue color
    displayPyramid(*this->selected_unit,this->selected_unit->fireRange, this->tabMapTile);
    glColor4f(1, 0.3, 0, 0.5);
    displayDestroyPyramid(*this->selected_unit,this->selected_unit->fireRange, this->tabMapTile);
  }
}

bool Game::validClickMove(int x, int y)
{
  if ((x >= 0 && y >= 0 && x < MAP_SIZE && y < MAP_SIZE) && (this->tabMapTile[(x)*MAP_SIZE + y].isWalkable) && (abs(this->selected_unit->x - x) + abs(this->selected_unit->y - y) <= this->selected_unit->dexterity))
  {
    //emepche d'aller sur d'autres unités
    for (int a = 0; a < this->nb_players; a++)
    {
      for (int b = 0; b < this->players[a].nbUnits; b++)
      {
        if (x == this->players[a].units[b].x && y == this->players[a].units[b].y)
        {
          return 0;
        }
      }
    }
    return 1;
  }
  else
  {
    cout << "Impossible de cliquer ici" << endl;
    return 0;
  }
}

bool Game::validClickAttack(int x, int y)
{
  if ((x >= 0 && y >= 0 && x < MAP_SIZE && y < MAP_SIZE) && (abs(this->selected_unit->x - x) + abs(this->selected_unit->y - y) <= this->selected_unit->fireRange))
  {
    return 1;
  }
  else
  {
    cout << "Impossible de tirer ici" << endl;
    return 0;
  }
}

void Game::clickCheck(float mouseX, float mouseY)
{

  float ratio = (float)this->surface->w / this->surface->h;

  float mouseXpos;
  float mouseYpos;

  int mouseTileX;
  int mouseTileY;

  if (ratio > 1)
  {
    mouseXpos = ((mouseX / this->surface->w) * ratio - 0.5 * ratio);
    mouseYpos = (mouseY / this->surface->h - 0.5);
  }
  else
  {
    mouseXpos = (mouseX / this->surface->w - 0.5);
    mouseYpos = ((mouseY / this->surface->h) * 1 / ratio - 0.5 * 1 / ratio);
  }
  float step = (float)0.5 / (MAP_SIZE / 2);

  if ((mouseXpos / step < -(MAP_SIZE / 2) && mouseXpos / step > -((MAP_SIZE / 2) + 1)) || (mouseYpos / step < -(MAP_SIZE / 2) && mouseYpos / step > -((MAP_SIZE / 2) + 1)))
  { //avoiding -0 symetry
    mouseTileX = MAP_SIZE / 2 + mouseXpos / step - 1;
    mouseTileY = MAP_SIZE / 2 + mouseYpos / step - 1;
  }
  else
  {
    mouseTileX = MAP_SIZE / 2 + mouseXpos / step;
    mouseTileY = MAP_SIZE / 2 + mouseYpos / step;
  }
  std::cout << "Tu as cliqué sur la case : " << mouseTileX << " ; " << mouseTileY << " : " << this->tabMapTile[mouseTileX * MAP_SIZE + mouseTileY].textureId << std::endl;
  if (mouseTileX >= 0 && mouseTileY >= 0 && mouseTileX < MAP_SIZE && mouseTileY < MAP_SIZE)
  {
    this->lastClickX = mouseTileX;
    this->lastClickY = mouseTileY;

    //Vérification de clic sur unité
    for (int y = 0; y < this->currentPlayer->nbUnits; y++)
    {
      if (mouseTileX == this->currentPlayer->units[y].x && mouseTileY == this->currentPlayer->units[y].y && this->currentPlayer->units[y].isDONE == false)
      {
        if (this->selected_unit != NULL && this->selected_unit->x == mouseTileX && this->selected_unit->y == mouseTileY && this->selected_unit->hasToAttack == false)
        {
          std::cout << "unité désélectionnée" << '\n';
          this->selected_unit = NULL;
        }
        else
        {
          if ((this->selected_unit != NULL && this->selected_unit->hasToAttack == false && this->selected_unit->isMoving == false) || this->selected_unit == NULL)
          {
            this->selected_unit = &currentPlayer->units[y];
            std::cout << "unité cliquée" << std::endl;
          }
        }
      }
    }

    if (this->selected_unit != NULL && !(lastClickX == this->selected_unit->x && lastClickY == this->selected_unit->y) && this->moving_unit == false && this->selected_unit->hasToAttack == false && validClickMove(lastClickX, lastClickY))
    {
      //this->moving_unit = true;
      this->selected_unit->currentPath = aStar(this->tabMapTile, this->selected_unit->x, this->selected_unit->y, this->lastClickX, this->lastClickY);
      this->selected_unit->isMoving = true;
      deplacement(this->selected_unit, lastClickX, lastClickY);
    }
    if (this->selected_unit != NULL && this->moving_unit == false && this->selected_unit->hasToAttack == true && validClickAttack(lastClickX, lastClickY))
    {
      cout << "FUS RO DAH" << endl;

      //check where firing
      //FRIENDLY FIRE ACTIVATED
      for (int o = 0; o < this->nb_players; o++)
      {
        for (int p = 0; p < this->players[o].nbUnits; p++)
        {
          int xTargetCheck = this->players[o].units[p].x;
          int yTargetCheck = this->players[o].units[p].y;
          if (lastClickX == xTargetCheck && lastClickY == yTargetCheck)
          {
            cout << "Bim !" << endl;
            attackUnit(this->selected_unit, &this->players[o].units[p]);
          }
          else{
            destroyEnvironnement(this->tabMapTile, lastClickX,lastClickY);
          }
        }
      }

      this->selected_unit->hasToAttack = false;
      this->selected_unit->isDONE = true;
      this->selected_unit = nullptr;
    }
  }
}



void Game::changeState(bool state)
{
  isRunning = state;
}

void Game::clean()
{

  /* AJOUTER LE CLEAN DES TEXTURES*/
  TTF_Quit();
  SDL_FreeSurface(this->surface);
  glDisable(GL_TEXTURE_2D);
  Mix_FreeMusic(this->music);
  Mix_FreeChunk(this->click);
  SDL_Quit();
  exit(EXIT_SUCCESS);
}
