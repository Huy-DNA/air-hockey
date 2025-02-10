#include "constants.hpp"
#include "keystate.hpp"
#include "match.hpp"
#include "state.hpp"
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

  KeyState keyStates;
  Stat stat{0, 0};
  Match match;
  GameState state = GameState::NO_MATCH;
  while (true) {
    // Event handling
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        state = GameState::QUIT;
      } else if (e.type == SDL_KEYDOWN) {
        // Collect key events
        keyStates.set(e.key.keysym.sym);
      } else if (e.type == SDL_KEYUP) {
        keyStates.reset(e.key.keysym.sym);
      }
    }

    // Switch behavior based on game state
    switch (state) {
    case GameState::NO_MATCH: {
      match.softReset();
      state = GameState::IN_MATCH;
      break;
    }
    case GameState::IN_MATCH: {
      const Match::Winner winner = match.step(stat, keyStates);
      if (winner == Match::Winner::RED) {
        state = GameState::NO_MATCH;
        ++stat.red;
      } else if (winner == Match::Winner::BLUE) {
        state = GameState::NO_MATCH;
        ++stat.blue;
      }
      break;
    }
    case GameState::QUIT: {
      goto quit;
    }
    }
  }
quit:

  IMG_Quit();
  Mix_Quit();
  TTF_Quit();
  SDL_Quit();
}
