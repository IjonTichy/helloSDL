#ifndef _HELLOSDL_RENDER__
#define _HELLOSDL_RENDER__

#include <exception>
#include <SDL/SDL.h>

#define LM_ADD          0
#define LM_MULTIPLY     1

using namespace std;

typedef struct lightmod_t
{
    int r; int g; int b;
    int mode;

    bool operator == (const lightmod_t x) const
    {
        if (r == x.r && g == x.g && b == x.b && mode == x.mode) { return 1; }
        return 0;
    }

    bool operator < (const lightmod_t x) const
    {
        if (mode > x.mode) { return 0; } if (mode < x.mode) { return 1; }
        if (r > x.r) { return 0; }  if (r < x.r) { return 1; }
        if (g > x.g) { return 0; }  if (g < x.g) { return 1; }
        if (b < x.b) { return 1; }

        return 0;
    }
} lightmod_t;

class InvalidLightMode: public exception
{
    protected:
        const char* reason;

    public:
        InvalidLightMode(const char* reason);
        virtual const char* what() const throw();
};

const lightmod_t lightmod_black     = {0,   0,   0,   LM_ADD};
const lightmod_t lightmod_normal    = {256, 256, 256, LM_ADD};
const lightmod_t lightmod_white     = {512, 512, 512, LM_ADD};

int blit(int x, int y, SDL_Surface* source, SDL_Surface* dest);
int blit_wh(int x, int y, int w, int h, SDL_Surface* source, SDL_Surface* dest);

int guaranteeInit(uint32_t flags);
SDL_Surface* initScreen(void);

Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

SDL_Surface* skeletonSurface(SDL_Surface* src);
SDL_Surface* tintSurface(SDL_Surface* src, lightmod_t tint) throw (InvalidLightMode);

#endif
