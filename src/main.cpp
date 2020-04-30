#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "game.hpp"
#include "constants.hpp"
#include "texture.hpp"
#include "player.hpp"

#include <string.h>

#include <iostream>

Game *game = nullptr;

int main(int argc, const char *argv[])
{
    game = new Game();

    game->init("IMAC WARS 2", WINDOW_WIDTH, WINDOW_HEIGHT);

    //init_textures(game->nb_textures_map, game->textureIds_map,game->textureLink);
    //printf("%d\n",game->textureLink[MAP_SIZE -17]); //Test pour voir si le tableau était rempli en sortie

    player newPlayer;
    initPlayer(&newPlayer, 1, 3);
    std::cout << newPlayer.resources << std::endl;

    while (game->running())
    {
        game->handleEvents();
        game->update();
        game->draw(game->surface);
    }

    game->clean();
    return 0;
}
