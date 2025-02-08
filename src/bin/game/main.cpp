#include "bat.hpp"
#include "board.hpp"
#include "constants.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_timer.h>
#include <cstdio>

int main(int argc, const char *argv[]) {
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0 || TTF_Init() < 0 ||
      IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0 || Mix_Init(MIX_INIT_MP3) < 0) {
    printf("SDL could not initialize! Error: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_SetWindowIcon(WINDOW, ICON_SURFACE);

  Board board = Board(FIELD_TEXTURE, 0, 0, FIELD_WIDTH, FIELD_HEIGHT);
  Bat blueBat = Bat(BAT_BLUE_TEXTURE, board.getBlueBatInitX(),
                    board.getBlueBatInitY(), BAT_SIZE);
  Bat redBat = Bat(BAT_RED_TEXTURE, board.getRedBatInitX(),
                   board.getRedBatInitY(), BAT_SIZE);

  bool quit = false;
  unsigned long long prevTicks = SDL_GetTicks64();
  while (!quit) {
    // Prolog
    unsigned long long curTicks = SDL_GetTicks64();
    unsigned long long deltaMs = curTicks - prevTicks; 

    // Event handling
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {
        const auto key = e.key.keysym.sym;
        const unsigned int step = deltaMs;
        switch (key) {
          case SDLK_a:
            blueBat.setX(blueBat.getX() - step);
            break;
          case SDLK_s:
            blueBat.setY(blueBat.getY() + step);
            break;
          case SDLK_d:
            blueBat.setX(blueBat.getX() + step);
            break;
          case SDLK_w:
            blueBat.setY(blueBat.getY() - step);
            break;
          case SDLK_LEFT:
            redBat.setX(blueBat.getX() - step);
            break;
          case SDLK_DOWN:
            redBat.setY(blueBat.getY() + step);
            break;
          case SDLK_RIGHT:
            redBat.setX(blueBat.getX() + step);
            break;
          case SDLK_UP:
            redBat.setY(blueBat.getY() - step);
            break;
        }
      }
    }

    // Render image
    SDL_RenderClear(RENDERER);
    board.draw(RENDERER);
    blueBat.draw(RENDERER);
    redBat.draw(RENDERER);
    SDL_RenderPresent(RENDERER);

    // Epilog
    while (SDL_GetTicks64() - curTicks < 1000 / 60);
    prevTicks = curTicks;
  }

  IMG_Quit();
  Mix_Quit();
  TTF_Quit();
  SDL_Quit();
}
