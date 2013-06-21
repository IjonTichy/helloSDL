#ifndef _HELLOSDL_MAIN__

  #define _HELLOSDL_MAIN__

  #include <SDL/SDL.h>

  void blit(int x, int y, SDL_Surface * source, SDL_Surface * dest);
  void blit_wh(int x, int y, int w, int h, SDL_Surface * source, SDL_Surface * dest);

  SDL_Surface * loadImage(char * filename);
  SDL_Surface * initScreen();

#endif
