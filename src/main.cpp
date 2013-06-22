#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "const.h"

#include "main.h"
#include "render.h"
#include "level.h"

void close(void)
{
    freeTiles();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
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
    mainloop(screen);
    close();
    
    return 0;
}

int mainloop(SDL_Surface * screen)
{
    Level tmp;
    SDL_Event event;

    int x = 0, y = 0;
    int xscroll = 0, yscroll = 0;

    if (tmp.fromFile("herpaderp.lvl"))
    {
        fprintf(stderr, "%s: error: file \"herpaderp.lvl\" doesn't exist\n", PROGNAME);
        return 1;
    }

    drawLevel(0, 0, screen, tmp);
    SDL_UpdateRect(screen, 0,0,0,0);

    while (1)
    {
        x += xscroll;
        y += yscroll;
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        drawLevel(x, y, screen, tmp);
        SDL_UpdateRect(screen, 0,0,0,0);

        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
              case SDL_QUIT:
                return 1;
                break;
            }

            // This will be massively cleaned up later
            
            if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
            {
                SDLKey key = event.key.keysym.sym;

                if (event.type == SDL_KEYDOWN)
                {
                    switch (key)
                    {
                      case SDLK_ESCAPE: return 1; 
                      case SDLK_LEFT: xscroll--; break; 
                      case SDLK_RIGHT: xscroll++; break;
                      case SDLK_UP: yscroll--; break;
                      case SDLK_DOWN: yscroll++; break;
                    }
                }
                else  // must be KEYUP
                {
                    switch (key)
                    {
                      case SDLK_LEFT: xscroll++; break;
                      case SDLK_RIGHT: xscroll--; break;
                      case SDLK_UP: yscroll++; break;
                      case SDLK_DOWN: yscroll--; break;
                    }
                }
            }
        }

        SDL_Delay(1);
    }

    return 0;
}
