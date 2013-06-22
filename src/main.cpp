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
    int i, endMainloop = 0;

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

    Level tmp;

    tmp.fromFile("herpaderp.lvl");

    while (1)
    {
        SDL_Event event;    
        SDL_WaitEvent(&event);
        
        if (&event != NULL)
        {
            switch (event.type)
            {
              case SDL_VIDEOEXPOSE:
                SDL_UpdateRect(screen, 0,0,0,0);
                break;

              case SDL_ACTIVEEVENT:
                drawLevel(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, screen);
                SDL_UpdateRect(screen, 0,0,0,0);
                break;

              case SDL_QUIT:
                endMainloop = 1;
                break;
            }
        }

        if (endMainloop) { break; }
    }

    close();
    return 0;
}
