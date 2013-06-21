#ifndef _HELLOSDL_MAIN__
#define _HELLOSDL_MAIN__

#include <SDL/SDL.h>

#define TILECOUNT 2

#define ERRORSPRITE "res/error.png"

#define TILE_NOERRORSPRITE 1

extern int tile_errno;

void blit(int x, int y, SDL_Surface * source, SDL_Surface * dest);
void blit_wh(int x, int y, int w, int h, SDL_Surface * source, SDL_Surface * dest);
void drawLevel(int centerX, int centerY, SDL_Surface * screen);

// Returns the amount of tiles that failed to load properly, or -1 if an error occured
int initTiles(void);
int freeTiles(void);

SDL_Surface * loadImage(char * filename);
SDL_Surface * initScreen(void);

#endif
