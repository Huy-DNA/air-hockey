#include "board.hpp"
#include "collision.hpp"
#include "constants.hpp"
#include "keystate.hpp"
#include "object/bat.hpp"
#include "object/puck.hpp"
#include "sprite.hpp"
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

  Bat blueBat = Bat(BAT_BLUE_SPRITE, board.getInitBlueBatPos(), BAT_SIZE / 2.0);
  Bat redBat = Bat(BAT_RED_SPRITE, board.getInitRedBatPos(), BAT_SIZE / 2.0);

  Puck puck = Puck(PUCK_SPRITE, board.getInitPuckPos(), PUCK_SIZE / 2.0);

  bool quit = false;
  unsigned long long prevTicks = SDL_GetTicks64();
  KeyState keyStates;
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
        // Collect key events
        keyStates.set(e.key.keysym.sym);
      } else if (e.type == SDL_KEYUP) {
        keyStates.reset(e.key.keysym.sym);
      }
    }

    // Update states
    /// Set velocity of bats
    unsigned long long step = deltaMs;
    blueBat.setVelocity({0.0, 0.0});
    if (keyStates.isTriggered(SDLK_a)) {
      blueBat.addVelocity({-1.0, 0.0});
    }
    if (keyStates.isTriggered(SDLK_d)) {
      blueBat.addVelocity({1.0, 0.0});
    }
    if (keyStates.isTriggered(SDLK_w)) {
      blueBat.addVelocity({0.0, -1.0});
    }
    if (keyStates.isTriggered(SDLK_s)) {
      blueBat.addVelocity({0.0, 1.0});
    }

    redBat.setVelocity({0.0, 0.0});
    if (keyStates.isTriggered(SDLK_LEFT)) {
      redBat.addVelocity({-1.0, 0.0});
    }
    if (keyStates.isTriggered(SDLK_RIGHT)) {
      redBat.addVelocity({1.0, 0.0});
    }
    if (keyStates.isTriggered(SDLK_UP)) {
      redBat.addVelocity({0.0, -1.0});
    }
    if (keyStates.isTriggered(SDLK_DOWN)) {
      redBat.addVelocity({0.0, 1.0});
    }

    // Split the movement & collision over the time period (50 rounds)
    // To prevent the phenomenon that deltaMs is too large, making the puck
    // penetrate through a colliding bat as the jump is too large
    for (int i = 0; i < 50; ++i) {
      /// Set position
      blueBat.move(deltaMs / 50.0);
      redBat.move(deltaMs / 50.0);
      puck.move(deltaMs / 50.0);

      /// Reflect
      reflectOffBat(puck, redBat);
      reflectOffBat(puck, blueBat);
      reflectOffBoard(puck, board);

      /// Adjust all the pieces' positions slightly to a consistent state
      uncollide(redBat, blueBat, puck, board);
    }

    // Render image
    SDL_RenderClear(RENDERER);
    board.draw(RENDERER);
    blueBat.draw(RENDERER);
    redBat.draw(RENDERER);
    puck.draw(RENDERER);
    SDL_RenderPresent(RENDERER);

    // Epilog
    while (SDL_GetTicks64() - curTicks < 1000 / 60)
      ;
    prevTicks = curTicks;
  }

  IMG_Quit();
  Mix_Quit();
  TTF_Quit();
  SDL_Quit();
}
