#include <string>
#include <exception>

#include <SDL/SDL.h>

#include "const.h"

#include "tile.h"
#include "render.h"
#include "loadData.h"

using namespace std;

int tile_errno;

Tile Tiles[TILECOUNT] = 
{
    Tile("res/floor.png"),
    Tile("res/wall.png"),
};

SDL_Surface* errorSprite;

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

int initSprites(void)
{
    int i;
    Tile* t;
    for (i = 0; i < TILECOUNT; i++)
    {
        t = &(Tiles[i]);
        t->initSprite();

        if (t->badSprite) { i++; }
    }

    return i;
}

Tile::Tile(string gfxPath = "") : spritePath ("res/error.png")
{
    if (gfxPath.length() != 0)
    {
        this->spritePath = gfxPath;
    }
}

void Tile::initSprite(void) throw (NoErrorSprite)
{
    SDL_Surface* sprite;
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

void Tile::Render(int x, int y, SDL_Surface* screen)
{
    if (x <= -TILE_WIDTH || x >= (int)screen->w
     || y <= -TILE_HEIGHT || y >= (int)screen->h) { return; }

    blit(x, y, this->sprite, screen);
}
