#ifndef _HELLOSDL_RENDER__
#define _HELLOSDL_RENDER__

#include <SDL/SDL.h>

typedef struct lightmod_t
{
    int r; int g; int b;

    bool operator == (const lightmod_t x) const
    {
        if (r == x.r && g == x.g && b == x.b) { return 1; }
        return 0;
    }

    bool operator < (const lightmod_t x) const
    {
        if (r > x.r) { return 0; }  if (r < x.r) { return 1; }
        if (g > x.g) { return 0; }  if (g < x.g) { return 1; }
        if (b < x.b) { return 1; }

        return 0;
    }
} lightmod_t;

const lightmod_t lightmod_black     = {0,   0,   0};
const lightmod_t lightmod_normal    = {256, 256, 256};
const lightmod_t lightmod_white     = {512, 512, 512};

int blit(int x, int y, SDL_Surface* source, SDL_Surface* dest);
int blit_wh(int x, int y, int w, int h, SDL_Surface* source, SDL_Surface* dest);

int guaranteeInit(uint32_t flags);
SDL_Surface* initScreen(void);

Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

SDL_Surface* skeletonSurface(SDL_Surface* src);
SDL_Surface* tintSurface(SDL_Surface* src, lightmod_t tint);

#endif
