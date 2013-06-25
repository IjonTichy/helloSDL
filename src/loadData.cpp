#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

SDL_Surface * loadImage(char * filename)
{
    SDL_Surface * rawImage = IMG_Load(filename);
 
    if (rawImage == NULL) { return rawImage; }

    SDL_Surface * ret = SDL_DisplayFormat(rawImage);
    SDL_FreeSurface(rawImage);

    return ret;
}

