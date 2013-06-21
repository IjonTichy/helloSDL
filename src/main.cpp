#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "const.h"

#include "render.h"
#include "level.h"

void close(void)
{
    freeTiles();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    int i;

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

    initTiles();
    drawLevel(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, screen);

    SDL_Flip(screen);
    SDL_Delay(5000);

    SDL_Quit();
    return 0;
}
