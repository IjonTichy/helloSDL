#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "render.h"

SDL_Surface* loadImage(char * filename)
{
    guaranteeInit(SDL_INIT_VIDEO);

    printf("loading \"%s\"...", filename);

    if (strlen(filename) <= 0) { return NULL; }

    SDL_Surface* rawImage = IMG_Load(filename);
 
    if (rawImage == NULL) { return rawImage; }

    SDL_Surface* ret = SDL_DisplayFormat(rawImage);
    SDL_FreeSurface(rawImage);

    printf("done. (%#x)\n", ret);

    return ret;
}

