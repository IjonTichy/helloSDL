#ifndef _HELLOSDL_RENDER__
#define _HELLOSDL_RENDER__

#include <SDL/SDL.h>
#include "level.h"

int blit(int x, int y, SDL_Surface * source, SDL_Surface * dest);
int blit_wh(int x, int y, int w, int h, SDL_Surface * source, SDL_Surface * dest);
void drawLevel(int centerX, int centerY, SDL_Surface * screen, Level level);

// Returns the amount of tiles that failed to load properly, or -1 if an error occured
SDL_Surface * initScreen(void);

#endif
