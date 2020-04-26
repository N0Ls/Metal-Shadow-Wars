#include "game.hpp"
#include "constants.hpp"
#include "texture.hpp"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


Game *game = nullptr;

int main(int argc, const char * argv[])
{
    game = new Game();

    game->init("IMAC WARS 2", WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_Surface *images[nb_textures];
    static char textures_paths[nb_textures][255]= {"doc/logo_imac.jpg", "doc/grass_block_side.png"};
    init_textures(textures_paths, nb_textures, images, textureIds);
    while (game->running())
    {
        game->handleEvents();
        game->update();
        game->draw(game->surface);

    }
    game->clean();
    return 0;
}
