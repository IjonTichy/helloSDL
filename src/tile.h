#ifndef _HELLOSDL_TILE__
#define _HELLOSDL_TILE__

#include <string>
#include <exception>
#include <SDL/SDL.h>

#define TILECOUNT 2
#define ERRORSPRITE "res/error.png"
#define TILE_NOERRORSPRITE 1

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

    public:
        Tile(string gfxPath);
        void initSprite(void) throw (NoErrorSprite);
        void Render(int x, int y, SDL_Surface* screen);

        char badSprite;
        SDL_Surface* sprite;
};

int initSprites(void);

extern Tile Tiles[TILECOUNT];

#endif
