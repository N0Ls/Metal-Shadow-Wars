#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "texture.hpp"
#include "constants.hpp"
using namespace std;


/**
 *
 * Initialize the textures for the map and the units
 *
 * @param nb_sub_groups The number of textures sub groups (map / units / etc.).
 * @param nb_textures_map The number of textures for the map.
 * @param nb_textures_units The number of textures for the units.
 * @param textureIds_map The palce we store the textures for the map.
 * @param textureIds_units The palce we store the textures for the units.
 *
 */
void init_textures(int nb_sub_groups,int nb_textures_map, int nb_textures_units, GLuint *textureIds_map, GLuint *textureIds_units){
  /* PATHS TO THE TEXTURES */
  char textures_paths_map[nb_textures_map][255]= { "assets/sprites/water.jpg","assets/sprites/tilebroken.jpg","assets/sprites/tile.jpg","assets/sprites/block.jpg" };
  char textures_paths_units[nb_textures_units][255] = { "assets/sprites/perso.png","assets/sprites/perso2.png", "assets/sprites/dog.png" };

  /* INIT SURFACES */
  SDL_Surface *images_map[nb_textures_map];
  SDL_Surface *images_units[nb_textures_units];

  /* LOAD THE IMAGES */
  for(int a=0 ; a < nb_sub_groups ; a ++){
    for(int i=0; i < nb_textures_map; i++){
      images_map[i] = IMG_Load(textures_paths_map[i]);
      if(NULL == images_map[i]) {
          fprintf(stderr, "Echec du chargement de l'image %s\n", textures_paths_map[i]);
          exit(EXIT_FAILURE);
      }
    }
    for(int y=0; y< nb_textures_units; y++){
      images_units[y] = IMG_Load(textures_paths_units[y]);
      if(NULL == images_units[y]) {
          fprintf(stderr, "Echec du chargement de l'image %s\n", textures_paths_units[y]);
          exit(EXIT_FAILURE);
      }
    }
    GLenum format;
    glGenTextures(nb_textures_map,&textureIds_map[0]);
    glGenTextures(nb_textures_units,&textureIds_units[0]);

    /* CREATING THE TEXTURES */
    for(int k=0; k< nb_textures_map; k++){
      glBindTexture(GL_TEXTURE_2D, textureIds_map[k]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

      switch(images_map[k]->format->BytesPerPixel){
        case 1:
              format = GL_RED;
              break;
          case 3:
              format = GL_RGB;
              break;
          case 4:
              format = GL_RGBA;
              break;
          default:
              fprintf(stderr, "Format des pixels de l'image %s non supporte.\n", textures_paths_map[k]);
              exit(EXIT_FAILURE);
      }
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,images_map[k]->w, images_map[k]->h, 0,format, GL_UNSIGNED_BYTE, images_map[k]->pixels);
      glBindTexture(GL_TEXTURE_2D, 0);
    }
    for(int j=0; j< nb_textures_units; j++){
      glBindTexture(GL_TEXTURE_2D, textureIds_units[j]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

      switch(images_units[j]->format->BytesPerPixel){
        case 1:
              format = GL_RED;
              break;
          case 3:
              format = GL_RGB;
              break;
          case 4:
              format = GL_RGBA;
              break;
          default:
              fprintf(stderr, "Format des pixels de l'image %s non supporte.\n", textures_paths_units[j]);
              exit(EXIT_FAILURE);
      }
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,images_units[j]->w, images_units[j]->h, 0,format, GL_UNSIGNED_BYTE, images_units[j]->pixels);
      glBindTexture(GL_TEXTURE_2D, 0);
    }
    SDL_FreeSurface(images_map[0]);
    SDL_FreeSurface(images_units[0]);

  }
}

void createSingleTexture(char *path , GLuint *textureContainer){
  SDL_Surface *surface;
  surface = IMG_Load(path);
  if(NULL == surface) {
      fprintf(stderr, "Echec du chargement de l'image %s\n", path);
      exit(EXIT_FAILURE);
  }
  GLenum format;
  glGenTextures(1,textureContainer);
    glBindTexture(GL_TEXTURE_2D, *textureContainer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    switch(surface->format->BytesPerPixel){
      case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            fprintf(stderr, "Format des pixels de l'image %s non supporte.\n", path);
            exit(EXIT_FAILURE);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,surface->w, surface->h, 0,format, GL_UNSIGNED_BYTE, surface->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);

}
