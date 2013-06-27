#include <SDL/SDL.h>

#include "const.h"
#include "level.h"
#include "tile.h"
#include "loadData.h"

#include "render.h"

int guaranteeInit(uint32_t flags)
{
    if (SDL_WasInit(flags) != flags)
    {
        if (!SDL_WasInit(SDL_INIT_EVERYTHING))
        {
            if (SDL_Init(SDL_INIT_EVERYTHING))
            {
                fprintf(stderr, "%s: error: SDL_Init failed: %s\n", PROGNAME, SDL_GetError());
                exit(1);
            }

            return 0;
        }
        else
        {
            if (SDL_InitSubSystem(flags))
            {
                fprintf(stderr, "%s: error: SDL_InitSubSystem failed: %s\n", PROGNAME, SDL_GetError());
                exit(1);
            }

            return 0;
        }
    }

    return 1;
}

SDL_Surface* initScreen(void)
{
    guaranteeInit(SDL_INIT_EVERYTHING);

    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SDL_SWSURFACE);

    if (screen == NULL)
    {
        fprintf(stderr, "%s: error: could not init screen: %s\n", PROGNAME, SDL_GetError());
        exit(1);
    }

    return screen;
}

int blit(int x, int y, SDL_Surface* source, SDL_Surface* dest)
{
    return blit_wh(x, y, source->w, source->h, source, dest);
}

int blit_wh(int x, int y, int w, int h, SDL_Surface* source, SDL_Surface* dest)
{
    SDL_Rect offset, size;
    int ret;

    offset.x = x; offset.y = y; offset.w = 0; offset.h = 0;
    size.x   = 0; size.y   = 0; size.w   = w; size.h   = h; 

    ret = SDL_BlitSurface(source, &size, dest, &offset);
    return ret;
}

/*
 * Taken straight from the SDL documentation
 *
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp)
    {
      case 1: return *p;
      case 2: return *(Uint16 *)p;

      case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) { return p[0] << 16 | p[1] << 8 | p[2]; }
        else { return p[0] | p[1] << 8 | p[2] << 16; }

      case 4: return *(Uint32 *)p;
      default: return 0;       /* shouldn't happen, but avoids warnings */
    }
}

/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp)
    {
      case 1: *p = pixel; break;
      case 2: *(Uint16 *)p = pixel; break;

      case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        }
        else
        {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

      case 4: *(Uint32 *)p = pixel; break;
    }
}
