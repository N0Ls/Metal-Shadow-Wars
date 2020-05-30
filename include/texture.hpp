#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

//structure of texture NOT USED
typedef struct{
  std::string image_path;
  std::string texture_name;
} texture;

//Declaration of prototypes
void init_textures(int nb_sub_groups,int nb_textures_map, int nb_textures_units, GLuint *textureIds_map, GLuint *textureIds_units ,GLuint *textureLink);

#endif
