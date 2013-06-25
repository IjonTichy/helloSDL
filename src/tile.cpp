#include <string>
#include <exception>

#include <SDL/SDL.h>

#include "tile.h"
#include "loadData.h"

using namespace std;

int tile_errno;

// TODO: remove TileFiles and TileSprites in favor of Tile class

char * TileFiles[TILECOUNT] = 
{
    "res/floor.png",
    "res/wall.png",
};

SDL_Surface * TileSprites[TILECOUNT] = {NULL};
SDL_Surface * errorSprite;


NoErrorSprite::NoErrorSprite(const char* reason = ""): reason ("Error sprite failed to load")
{
    if (strlen(reason)) { this->reason = reason; }
}

const char* NoErrorSprite::what() const throw()
{
    return (const char*)this->reason;
}


void loadErrorSprite(void)
{
    // load it now if not yet loaded
    if (errorSprite == NULL)
    {
        // we can get away with it potentially not loading for now
        errorSprite = loadImage(ERRORSPRITE);
    }
}

int initTiles(void) throw (NoErrorSprite)
{
    int i, ret = 0;
    SDL_Surface * sprite;

    loadErrorSprite();

    for (i = 0; i < TILECOUNT; i++)
    {
        sprite = loadImage(TileFiles[i]);

        if (sprite == NULL)
        {
            if (errorSprite == NULL) // oh shit it wasn't actually defined
            {
                NoErrorSprite noerr;
                throw noerr;
            }

            sprite = errorSprite;
            sprite->refcount++;

            ret++;
        }

        TileSprites[i] = sprite;
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

Tile::Tile(string gfxPath)
{
    if (gfxPath.length() != 0)
    {
        this->spritePath = gfxPath;
    }
    
    this->initSprite();
}

void Tile::initSprite(void)
{
    SDL_Surface * sprite;
    loadErrorSprite();
    
    this->badSprite = 0;
    sprite = loadImage((char*)this->spritePath.c_str());

    if (sprite == NULL)
    {
        if (errorSprite == NULL)  // wasn't defined oh_no
        {
            NoErrorSprite noerr;
            throw noerr;
        }

        sprite = errorSprite;
        sprite->refcount++;

        this->badSprite = 1;
    }

    this->sprite = sprite;
}
