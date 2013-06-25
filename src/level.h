#ifndef _HELLOSDL_LEVEL__
#define _HELLOSDL_LEVEL__

#include <vector>
#include <SDL/SDL.h>

#define LEVEL_H 16
#define LEVEL_W 16

using namespace std;

struct levelsize { unsigned int w; unsigned int h; };
typedef vector< vector<int> > MapVector;

class Level
{
    protected:
        unsigned int width, height;
        MapVector map;

    public:
        Level(void);
        int GetTile(int x, int y);
        int FromFile(char * filename);
        struct levelsize Size(void);
        void Render(SDL_Surface * screen, int originX, int originY);
};

#endif
