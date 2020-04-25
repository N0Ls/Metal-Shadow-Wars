#include "game.hpp"

static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;

Game *game = nullptr;

int main(int argc, const char * argv[])
{
    game = new Game();

    game->init("IMAC WARS 2", WINDOW_WIDTH, WINDOW_HEIGHT);

    while (game->running())
    {
        game->handleEvents();
        //game->update();
    }
    game->clean();
    return 0;
}