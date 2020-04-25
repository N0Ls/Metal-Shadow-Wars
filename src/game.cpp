#include "game.hpp"
#include "geometry.hpp"
#include <iostream>

static const unsigned int BIT_PER_PIXEL = 32;

Game::Game()
{
}

Game::~Game()
{
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
    SDL_Surface *surface;

    surface = SDL_SetVideoMode(
        width, height, BIT_PER_PIXEL,
        SDL_OPENGL | SDL_GL_DOUBLEBUFFER);

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

        default:
            break;
        }
    }
}
void Game::draw(){}
void Game::update()
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
    int k = 0;
    fillGrid();
    k++;
    std::cout << "counter "<< std::endl;
}

void Game::clean()
{
    SDL_Quit();
    exit(EXIT_SUCCESS);
}
