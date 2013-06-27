#ifndef _HELLOSDL_RENDER__
#define _HELLOSDL_RENDER__

#include <SDL/SDL.h>
#include "level.h"

int blit(int x, int y, SDL_Surface* source, SDL_Surface* dest);
int blit_wh(int x, int y, int w, int h, SDL_Surface* source, SDL_Surface* dest);

int guaranteeInit(uint32_t flags);
SDL_Surface* initScreen(void);

#endif
