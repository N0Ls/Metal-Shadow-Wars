#include "map.hpp"
#include "constants.hpp"
using namespace std;
#include <iostream>
#include "texture.hpp"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constants.hpp"



void setTile(TileMap *tile, GLuint textureId, bool isWalkable, bool isDestructible){
  tile->textureId=textureId;
  tile->isWalkable=isWalkable;
  tile->isDestructible=isDestructible;
}
void drawQuads(){
  glBegin(GL_QUADS);
    glColor3f(1,1,1);
      glTexCoord2f(0 ,0);
      glVertex2f(0,0);

      glTexCoord2f(1 ,0);
      glVertex2f(MAP_TILE_SIZE,0);

      glTexCoord2f( 1 , 1);
      glVertex2f(MAP_TILE_SIZE,MAP_TILE_SIZE);

      glTexCoord2f( 0 , 1);
      glVertex2f(0,MAP_TILE_SIZE);
  glEnd();
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

switch (bpp)
{
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
  }
}



void loadMap(TileMap *tabMapTile){
  SDL_Surface *mapLoad;
  SDL_Surface *mapColor;
  char mapLoadImage[255]= {"assets/map.png"};
  mapLoad = IMG_Load(mapLoadImage);
  if(NULL == mapLoad) {
      fprintf(stderr, "Echec du chargement de l'image %s\n",mapLoadImage );
      exit(EXIT_FAILURE);
  }

  //c'est juste
  SDL_PixelFormat *fmt;
  SDL_Surface *surface;
  surface=IMG_Load(mapLoadImage);
  Uint32 temp, pixel;
  Uint8 red, green, blue, alpha;

  fmt=surface->format;

  for (int i = 0; i < MAP_SIZE; i++) {
    for(int y = 0; y < MAP_SIZE;y++){
      SDL_LockSurface(surface);
      pixel=*((Uint32*)surface->pixels);
      pixel=getpixel(surface,y,i);
      SDL_UnlockSurface(surface);

      /* Get Red component */
      temp=pixel&fmt->Rmask; /* Isolate red component */
      temp=temp>>fmt->Rshift;/* Shift it down to 8-bit */
      temp=temp<<fmt->Rloss; /* Expand to a full 8-bit number */
      red=(Uint8)temp;

      /* Get Green component */
      temp=pixel&fmt->Gmask; /* Isolate green component */
      temp=temp>>fmt->Gshift;/* Shift it down to 8-bit */
      temp=temp<<fmt->Gloss; /* Expand to a full 8-bit number */
      green=(Uint8)temp;

      /* Get Blue component */
      temp=pixel&fmt->Bmask; /* Isolate blue component */
      temp=temp>>fmt->Bshift;/* Shift it down to 8-bit */
      temp=temp<<fmt->Bloss; /* Expand to a full 8-bit number */
      blue=(Uint8)temp;

      /* Get Alpha component */
      temp=pixel&fmt->Amask; /* Isolate alpha component */
      temp=temp>>fmt->Ashift;/* Shift it down to 8-bit */
      temp=temp<<fmt->Aloss; /* Expand to a full 8-bit number */
      alpha=(Uint8)temp;

      //printf("Pixel Color -> R: %d,  G: %d,  B: %d,  A: %d\n", red, green, blue, alpha);

      if(red == 255 && green ==0 && blue ==0){
        setTile(&tabMapTile[y*MAP_SIZE + i],3,0,1);
      }
      else if(red == 0 && green ==255 && blue ==0){
        setTile(&tabMapTile[y*MAP_SIZE + i],2,1,0);
      }
      else if(red == 0 && green ==0 && blue ==255){
        setTile(&tabMapTile[y*MAP_SIZE + i],0,0,0);
      }
      else{
        setTile(&tabMapTile[y*MAP_SIZE + i],0,0,0);
      }
    }
  }
}

void destroyEnvironnement(TileMap *tabMapTile, int x , int y){
  if(tabMapTile[x*MAP_SIZE + y].isDestructible){
      setTile(&tabMapTile[x*MAP_SIZE + y],2,1,0);
  }
}

void fillGrid(GLuint textureIds[],GLuint textureLink[], TileMap *tabMapTile){
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPushMatrix();
    glScalef(1,-1,1.);
    int t =0;
    for (int i = 0; i < MAP_SIZE; i++) {
      for (int y = 0; y < MAP_SIZE; y++) {
          glPushMatrix();
            glTranslatef((-GL_VIEW_SIZE/2)+i*MAP_TILE_SIZE,(-GL_VIEW_SIZE/2)+y*MAP_TILE_SIZE,0);
            glBindTexture(GL_TEXTURE_2D, textureIds[tabMapTile[i*MAP_SIZE + y].textureId]);
            drawQuads();

            // if (textureLink[t] < 6){
            //   glBindTexture(GL_TEXTURE_2D, textureIds[textureLink[t]]);
            // }
            // else {
            //   glBindTexture(GL_TEXTURE_2D, textureIds[textureLink[2]]);
            // }
            drawQuads();
          glPopMatrix();
          t++;
      }
    }

  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D, 0);
}
