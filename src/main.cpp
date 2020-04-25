#include "game.hpp"
#include "constants.hpp"


Game *game = nullptr;

int main(int argc, const char * argv[])
{
    game = new Game();

    game->init("IMAC WARS 2", WINDOW_WIDTH, WINDOW_HEIGHT);

    while (game->running())
    {
        game->handleEvents();
        game->update();
        game->draw(game->surface);

    }
    game->clean();
    return 0;
}
