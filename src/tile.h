#ifndef _HELLOSDL_TILE__
#define _HELLOSDL_TILE__

#include <string>
#include <exception>
#include <SDL/SDL.h>

#define TILECOUNT 2
#define ERRORSPRITE "res/error.png"
#define TILE_NOERRORSPRITE 1

extern SDL_Surface * TileSprites[TILECOUNT];

using namespace std;

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
        string spritePath;
        void initSprite(void);

    public:
        char badSprite;
        Tile(string gfxPath);
        SDL_Surface * sprite;
};

int initTiles(void) throw (NoErrorSprite);
int freeTiles(void);

#endif
