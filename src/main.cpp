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
        fprintf(stderr, "%s: error: SDL_Init failed: %s\n", PROGNAME, SDL_GetError());
        return 1;
    }

    SDL_Surface * screen = initScreen();

    if (screen == NULL)
    {
        fprintf(stderr, "%s: error: could not init screen: %s\n", PROGNAME, SDL_GetError());
        return 1;
    }

    initTiles();

    Level tmp;

    if (tmp.fromFile("herpaderp.lvl"))
    {
        fprintf(stderr, "%s: error: file \"herpaderp.lvl\" doesn't exist\n", PROGNAME);
        return 1;
    }

    drawLevel(0, 0, screen, tmp);
    SDL_UpdateRect(screen, 0,0,0,0);

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
                drawLevel(0, 0, screen, tmp);
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
