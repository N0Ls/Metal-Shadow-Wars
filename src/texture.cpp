#include "texture.hpp"
#include <string.h>
using namespace std;
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>





void init_textures(char textures_paths[][255], int nb_textures, SDL_Surface *images[], GLuint textureIds[]){


  //load images
  for(int i=0; i < nb_textures; i++){
    images[i] = IMG_Load(textures_paths[i]);
    if(NULL == images[i]) {
        fprintf(stderr, "Echec du chargement de l'image %s\n", textures_paths[i]);
        exit(EXIT_FAILURE);
    }
  }
  //binding machin



  GLenum format;
  for(int y=0; y< nb_textures; y++){
    glGenTextures(1,&textureIds[y]);
    glBindTexture(GL_TEXTURE_2D, textureIds[y]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    switch(images[y]->format->BytesPerPixel){
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
            fprintf(stderr, "Format des pixels de l'image %s non supporte.\n", textures_paths[y]);
            exit(EXIT_FAILURE);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,images[y]->w, images[y]->h, 0,format, GL_UNSIGNED_BYTE, images[y]->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

}



//
// if(NULL == image) {
//     fprintf(stderr, "Echec du chargement de l'image %s\n", image_path);
//     exit(EXIT_FAILURE);
// }
