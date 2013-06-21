#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "main.h"
#include "const.h"

SDL_Surface * loadImage(char * filename)
{
    SDL_Surface * rawImage = IMG_Load(filename);
 
    if (rawImage == NULL) { return rawImage; }

    SDL_Surface * ret = SDL_DisplayFormat(rawImage);
    SDL_FreeSurface(rawImage);

    return ret;
}

SDL_Surface * initScreen()
{
    SDL_Surface * ret = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SDL_SWSURFACE);

    // do error checking here later, once we have a purpose for this project

    return ret;
}

void blit(int x, int y, SDL_Surface * source, SDL_Surface * dest)
{
    blit_wh(x, y, source->w, source->h, source, dest);
}

void blit_wh(int x, int y, int w, int h, SDL_Surface * source, SDL_Surface * dest)
{
    SDL_Rect offset, size;

    offset.x = x; offset.y = y;
    size.w   = w; size.h = h;

    SDL_BlitSurface(source, &size, dest, &offset);
}

    

#pragma GCC diagnostic ignored "-Wwrite-strings"

int main( int argc, char* args[] )
{
    int x, y;

    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        fprintf(stderr, "%s: error: SDL_Init failed: %s", PROGNAME, SDL_GetError());
        return 1;
    }

    SDL_Surface * screen = initScreen();

    if (screen == NULL)
    {
        fprintf(stderr, "%s: error: could not init screen: %s", PROGNAME, SDL_GetError());
        return 1;
    }

    SDL_Surface * wall = loadImage("res/wall.png");
    x = (SCREEN_WIDTH  - wall->w) / 2;
    y = (SCREEN_HEIGHT - wall->h) / 2;

    blit(x, y, wall, screen);

    SDL_Flip(screen);

    SDL_Delay(5000);

    SDL_Quit();
    return 0;
}

#pragma GCC diagnostic pop
