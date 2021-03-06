#ifndef _HELLOSDL_LEVEL__
#define _HELLOSDL_LEVEL__

#include <vector>
#include <SDL/SDL.h>
#include "tile.h"

#define LEVEL_H 16
#define LEVEL_W 16

using namespace std;

class Tile;

struct levelsize { unsigned int w; unsigned int h; };
typedef vector<Tile*> TileVector;
typedef vector<TileVector> MapVector;

class Level
{
    protected:
        unsigned int width, height;
        MapVector map;

    public:
        Level(void);
        Tile* GetTile(int x, int y);
        int FromFile(char * filename);
        struct levelsize Size(void);
        void Render(SDL_Surface* screen, int originX, int originY);
        TileVector TileLine(int x1, int y1, int x2, int y2);
};

#endif
