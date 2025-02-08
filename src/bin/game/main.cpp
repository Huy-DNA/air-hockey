#include "board.hpp"
#include "constants.hpp"
#include "sdl_utils.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <cstdio>

int main(int argc, const char *argv[]) {
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0 || TTF_Init() < 0 ||
      IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0 || Mix_Init(MIX_INIT_MP3) < 0) {
    printf("SDL could not initialize! Error: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_SetWindowIcon(WINDOW, ICON_SURFACE);

  Board board = Board::create(FIELD_TEXTURE,
                              createRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

  bool quit = false;
  while (!quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }

    SDL_RenderClear(RENDERER);
    board.draw(RENDERER);
    SDL_RenderPresent(RENDERER);
  }

  IMG_Quit();
  Mix_Quit();
  TTF_Quit();
  SDL_Quit();
}
