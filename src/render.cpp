#include <SDL/SDL.h>

#include "const.h"
#include "level.h"
#include "tile.h"
#include "loadData.h"

#include "render.h"

SDL_Surface * initScreen(void)
{
    SDL_Surface * ret = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SDL_SWSURFACE);

    // do error checking here later, once we have a purpose for this project

    return ret;
}

int blit(int x, int y, SDL_Surface * source, SDL_Surface * dest)
{
    return blit_wh(x, y, source->w, source->h, source, dest);
}

int blit_wh(int x, int y, int w, int h, SDL_Surface * source, SDL_Surface * dest)
{
    SDL_Rect offset, size;
    int ret;

    offset.x = x; offset.y = y; offset.w = 0; offset.h = 0;
    size.x   = 0; size.y   = 0; size.w   = w; size.h   = h; 

    ret = SDL_BlitSurface(source, &size, dest, &offset);
    return ret;
}


void drawLevel(int baseX, int baseY, SDL_Surface * screen, Level level)
{
    unsigned int i, j, x, y;
    int tile;

    struct levelsize size = level.Size();

    for (i = 0; i < size.w; i++)
    {
        for (j = 0; j < size.h; j++)
        {
            x = baseX + (TILE_WIDTH  * i);
            y = baseY + (TILE_HEIGHT * j);
            tile = level.GetTile(i, j);

            if (tile == -1) { continue; }

            blit(x, y, TileSprites[tile], screen);
        }
    }
}
