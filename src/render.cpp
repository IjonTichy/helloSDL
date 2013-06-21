#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "const.h"
#include "level.h"

#include "render.h"

int tile_errno;

const char * TileFiles[TILECOUNT] = 
{
    "res/floor.png",
    "res/wall.png",
};

SDL_Surface * TileSprites[TILECOUNT] = {NULL};

SDL_Surface * loadImage(char * filename)
{
    SDL_Surface * rawImage = IMG_Load(filename);
 
    if (rawImage == NULL) { return rawImage; }

    SDL_Surface * ret = SDL_DisplayFormat(rawImage);
    SDL_FreeSurface(rawImage);

    return ret;
}

SDL_Surface * initScreen(void)
{
    SDL_Surface * ret = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SDL_HWSURFACE);

    // do error checking here later, once we have a purpose for this project

    return ret;
}

int initTiles(void)
{
    int i, ret = 0;
    SDL_Surface * sprite;

    // we can get away with it potentially not loading...
    SDL_Surface * errorSprite = IMG_Load(ERRORSPRITE);

    for (i = 0; i < TILECOUNT; i++)
    {
        sprite = IMG_Load(TileFiles[i]);

        if (sprite == NULL)
        {
            // ... up until here.

            if (errorSprite == NULL)
            {
                tile_errno = TILE_NOERRORSPRITE;
                return -1;
            }

            sprite = errorSprite;
            sprite->refcount++;

            ret++;
        }

        printf("set tile %d (\"%s\") - ret is %d\n", i, TileFiles[i], ret);
        TileSprites[i] = sprite;
    }

    if (ret == 0)
    {
        SDL_FreeSurface(errorSprite);
    }
    
    return ret;
}

int freeTiles(void)
{
    int i, ret = 0;
    SDL_Surface * sprite;

    for (i = 0; i < TILECOUNT; i++)
    {
        sprite = TileSprites[i];
        if (sprite->refcount == 0) { ret++; continue; }

        SDL_FreeSurface(sprite);
    }

    return ret;
}

void blit(int x, int y, SDL_Surface * source, SDL_Surface * dest)
{
    blit_wh(x, y, source->w, source->h, source, dest);
}

void blit_wh(int x, int y, int w, int h, SDL_Surface * source, SDL_Surface * dest)
{
    SDL_Rect offset, size;

    offset.x = x; offset.y = y;
    size.w   = w; size.h = h;

    SDL_BlitSurface(source, &size, dest, &offset);
}


void drawLevel(int centerX, int centerY, SDL_Surface * screen)
{
    int i, j, x, y, tile;

    int baseX = centerX - ((TILE_WIDTH * LEVEL_W) / 2);
    int baseY = centerY - ((TILE_WIDTH * LEVEL_H) / 2);

    for (i = 0; i < LEVEL_W; i++)
    {
        for (j = 0; j < LEVEL_H; j++)
        {
            x = baseX + (TILE_WIDTH  * i);
            y = baseY + (TILE_HEIGHT * j);
            tile = getTile(i, j);

            printf("blitting tile %d (%d, %d) to (%d, %d)\n", tile, i, j, x, y);

            blit(x, y, TileSprites[tile], screen);
        }
    }
}
