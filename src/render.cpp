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
