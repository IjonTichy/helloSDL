#ifndef _HELLOSDL_TILE__
#define _HELLOSDL_TILE__

#include <string>
#include <exception>
#include <map>
#include <SDL/SDL.h>

#include "level.h"

#define TILECOUNT 2
#define ERRORSPRITE "res/error.png"
#define TILE_NOERRORSPRITE 1

using namespace std;

class Level;

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

typedef map<lightmod_t, SDL_Surface*> spritecache_t;
typedef map<string, spritecache_t*> spritemap_t;

const lightmod_t lightmod_black     = {0,   0,   0};
const lightmod_t lightmod_normal    = {256, 256, 256};
const lightmod_t lightmod_white     = {512, 512, 512};

class NoErrorSprite: public exception
{
    protected:
        const char* reason;

    public:
        NoErrorSprite(const char* reason);
        virtual const char* what() const throw();
};

class Tile
{

    protected:
        static spritemap_t cached_sprites;
        static SDL_Surface* get_cached_sprite(string Path, lightmod_t lightLevel);
        static void add_cached_sprite(string path, SDL_Surface* sprite, lightmod_t lightLevel);
        static void clear_cached_sprites(void);

        const char* my_name;
        string sprite_path;
        Level* my_level;

        void init_sprite(void) throw (NoErrorSprite);

    public:
        Tile(Level* l, string gfxPath);
        void LoadSprite(void);
        void Render(int x, int y, SDL_Surface* screen);

        bool badSprite;
        SDL_Surface* sprite;
};

int initSprites(void);

#endif
