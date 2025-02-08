#include "game.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <cstdio>

int main(int argc, const char *argv[]) {
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0 || TTF_Init() < 0 ||
      IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0 || Mix_Init(MIX_INIT_WAVPACK)) {
    printf("SDL could not initialize! Error: %s\n", SDL_GetError());
    exit(1);
  } 

  Game game;
  game.start();

  IMG_Quit();
  Mix_Quit();
  TTF_Quit();
  SDL_Quit();
}
