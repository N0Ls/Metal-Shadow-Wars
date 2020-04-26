#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

typedef struct{
  std::string image_path;
  std::string texture_name;
} texture;

void init_textures(char textures_paths[][255], int nb_textures, SDL_Surface *images[], GLuint *textureIds);

#endif