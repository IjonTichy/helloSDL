#ifndef _HELLOSDL_TILE__
#define _HELLOSDL_TILE__

#include <string>
#include <exception>
#include <map>
#include <SDL/SDL.h>

#include "level.h"
#include "render.h"

#define TILECOUNT 2
#define ERRORSPRITE "res/error.png"
#define TILE_NOERRORSPRITE 1

using namespace std;

class Level;

typedef map<lightmod_t, SDL_Surface*> spritecache_t;
typedef map<string, spritecache_t*> spritemap_t;

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
        lightmod_t tmp_tint;
        unsigned int x, y;

        void init_sprite(lightmod_t tint) throw (NoErrorSprite);

    public:
        static void PrintCache(void);
        static int CacheSize(void);

        Tile(Level* l, unsigned int x, unsigned int y, string gfxPath = "", lightmod_t tint = lightmod_normal);
        void LoadSprite(void);
        void Render(int x, int y, SDL_Surface* screen);

        bool badSprite;
        SDL_Surface* sprite;
};

int initSprites(void);

#endif
