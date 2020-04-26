#include "game.hpp"
#include "map.hpp"
#include "constants.hpp"
#include <iostream>

static const unsigned int BIT_PER_PIXEL = 32;

Game::Game()
{
}

Game::~Game()
{
}
void Game::reshape(SDL_Surface** surface, unsigned int width, unsigned int height)
{

    static float aspectRatio;
    SDL_Surface* surface_temp = SDL_SetVideoMode(
        width, height, BIT_PER_PIXEL,
        SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);
    if(NULL == surface_temp)
    {
        fprintf(
            stderr,
            "Erreur lors du redimensionnement de la fenetre.\n");
        exit(EXIT_FAILURE);
    }
    *surface = surface_temp;

    aspectRatio = width / (float) height;

    glViewport(0, 0, (*surface)->w, (*surface)->h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if( aspectRatio > 1)
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    reshape(&surface, width, height);

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
            break;
        }

        /* Close window */
        if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
        {
            isRunning = false;
            break;
        }

        switch (e.type)
        {
        /* Clic souris */
        case SDL_MOUSEBUTTONUP:
            printf("clic en (%d, %d)\n", e.button.x, e.button.y);
            break;

        /* Mouvement souris */
        case SDL_MOUSEMOTION:
            //printf("souris en (%d, %d)\n", e.button.x, e.button.y);
            break;

        /* Touche clavier */
        case SDL_KEYDOWN:
            printf("touche pressee (code = %d)\n", e.key.keysym.sym);
            break;
        case SDL_VIDEORESIZE:
            reshape(&surface, e.resize.w, e.resize.h);
            break;
        default:
            break;
        }
    }
}
void Game::draw(SDL_Surface *surface){
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    fillGrid(surface);

}
void Game::update()
{

    int k = 0;

    k++;
    //std::cout << "counter "<< std::endl;
}

void Game::clean()
{
  /* AJOUTER LE CLEAN DES TEXTURES*/
    SDL_Quit();
    exit(EXIT_SUCCESS);
}