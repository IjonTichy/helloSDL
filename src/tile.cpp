#include <string>
#include <typeinfo>
#include <exception>
#include <iostream>

#include <SDL/SDL.h>
#include <cxxabi.h>

#include "const.h"

#include "level.h"
#include "render.h"
#include "loadData.h"

#include "tile.h"

using namespace std;

int tile_errno;

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

spritemap_t Tile::cached_sprites;

// TODO: Better way of including tints in the tile

Tile::Tile(Level* l, string gfxPath, lightmod_t tint) : sprite_path ("res/error.png")
{
    this->my_level = l;
    this->tmp_tint = tint;
    this->sprite = NULL;

#if defined(__GNUC__)
    int status;
    this->my_name = abi::__cxa_demangle(typeid(*this).name(), 0, 0, &status);
#else
    this->my_name = typeid(*this).name();
#endif

    if (gfxPath.length() != 0)
    {
        this->sprite_path = gfxPath;
    }

    this->LoadSprite();
}

void Tile::LoadSprite(void)
{
    SDL_Surface* cachedSprite = Tile::get_cached_sprite(this->sprite_path, this->tmp_tint);

    if (cachedSprite == NULL)
    {
        this->init_sprite(this->tmp_tint);
    }
    else
    {
        if (this->sprite != cachedSprite && this->sprite != NULL) // found a new sprite
        {
            SDL_FreeSurface(this->sprite);
        }

        cachedSprite->refcount++;
        this->sprite = cachedSprite;
    }
}

SDL_Surface* Tile::get_cached_sprite(string path, lightmod_t lightLevel)
{
    spritecache_t* cacheRow;
    spritecache_t::iterator cacheIter;

    if (!Tile::cached_sprites.count(path)) { return NULL; }

    cacheRow = Tile::cached_sprites[path];  // convenience

    if (!cacheRow->count(lightLevel)) { return NULL; }

    return (*cacheRow)[lightLevel];
}

void Tile::add_cached_sprite(string path, SDL_Surface* sprite, lightmod_t lightLevel)
{
    spritecache_t* cacheRow;
    SDL_Surface * curSprite;

    if (!Tile::cached_sprites.count(path))
    {
        Tile::cached_sprites[path] = new spritecache_t;
    }

    cacheRow = Tile::cached_sprites[path];
    curSprite = (*cacheRow)[lightLevel];

    if (curSprite == sprite) { return; }
    if (curSprite != sprite && curSprite != NULL)
    {
        SDL_FreeSurface(curSprite);
    }

    (*cacheRow)[lightLevel] = sprite;
    sprite->refcount++;
}

void Tile::clear_cached_sprites(void)
{
    spritemap_t::iterator rows;

    for (rows = Tile::cached_sprites.begin(); rows != Tile::cached_sprites.end(); ++rows)
    {
        delete rows->second;
        Tile::cached_sprites.erase(rows);
    }
}

void Tile::PrintCache(void)
{
    spritemap_t::iterator smIter;
    spritecache_t::iterator scIter;
    spritecache_t* row;
    lightmod_t tint;

    for (smIter = Tile::cached_sprites.begin(); smIter != Tile::cached_sprites.end(); ++smIter)
    {
        printf("%s:\n", smIter->first.c_str());
        row = smIter->second;

        for (scIter = row->begin(); scIter != row->end(); ++scIter)
        {
            tint = scIter->first;
            printf("  (%d, %d, %d): %#x\n", tint.r, tint.g, tint.b, scIter->second);
        }

        printf("\n");
    }
}

int Tile::CacheSize(void)
{
    int ret = 0;
    spritemap_t::iterator smIter;

    for (smIter = Tile::cached_sprites.begin(); smIter != Tile::cached_sprites.end(); ++smIter)
    {
        ret += smIter->second->size();
    }

    return ret;
}
void Tile::init_sprite(lightmod_t tint) throw (NoErrorSprite)
{
    SDL_Surface* sprite;
    SDL_Surface* newsprite;
    loadErrorSprite();

    this->badSprite = 0;
    sprite = Tile::get_cached_sprite(this->sprite_path, lightmod_normal);

    if (sprite == NULL)
    {
        sprite = loadImage((char*)this->sprite_path.c_str());

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

        Tile::add_cached_sprite(this->sprite_path, sprite, lightmod_normal);
    }

    if (!this->badSprite)
    {
        newsprite = tintSurface(sprite, tint);
        this->sprite = newsprite;
    }

    Tile::add_cached_sprite(this->sprite_path, this->sprite, tint);
}

void Tile::Render(int x, int y, SDL_Surface* screen)
{
    if (x <= -TILE_WIDTH || x >= (int)screen->w
     || y <= -TILE_HEIGHT || y >= (int)screen->h) { return; }

    blit(x, y, this->sprite, screen);
}
