#include "constants.hpp"
#include "keystate.hpp"
#include "match.hpp"
#include "menu.hpp"
#include "mousestate.hpp"
#include "state.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_mouse.h>
#include <SDL_timer.h>
#include <cstdio>

int main(int argc, const char *argv[]) {
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    exit(1);
  }
  if (TTF_Init() < 0) {
    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    exit(1);
  }
  if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
    printf("SDL_img could not initialize! SDL_img Error: %s\n", IMG_GetError());
    exit(1);
  }
  if (Mix_Init(MIX_INIT_MP3) < 0) {
    printf("SDL_img could not initialize! SDL_img Error: %s\n", Mix_GetError());
    exit(1);
  }

  SDL_SetWindowIcon(WINDOW, ICON_SURFACE);

  KeyState keyState;
  MouseState mouseState;
  MainMenu menu;
  Match match;
  GameState state = GameState::MAIN_MENU;
  while (true) {
    // Event handling
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        state = GameState::QUIT;
      } else if (e.type == SDL_KEYDOWN) {
        // Collect key events
        keyState.set(e.key.keysym.sym);
      } else if (e.type == SDL_KEYUP) {
        keyState.reset(e.key.keysym.sym);
      } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (e.button.button == SDL_BUTTON_LEFT) {
          mouseState.setLeft(MouseState::PRESSED);
        } else {
          mouseState.setRight(MouseState::PRESSED);
        }
      } else if (e.type == SDL_MOUSEBUTTONUP) {
        if (e.button.button == SDL_BUTTON_LEFT) {
          mouseState.setLeft(MouseState::UNPRESSED);
        } else {
          mouseState.setRight(MouseState::UNPRESSED);
        }
      }
    }
    {
      int x;
      int y;
      SDL_GetMouseState(&x, &y);
      mouseState.setPosition({x * 1.0f, y * 1.0f});
    }

    // Switch behavior based on game state
    switch (state) {
    case GameState::MAIN_MENU: {
      state = menu.step(mouseState);
      break;
    }
    case GameState::INSTRUCTION: {
      break;
    }
    case GameState::START_MATCH: {
      match.softReset();
      state = GameState::IN_MATCH;
      break;
    }
    case GameState::IN_MATCH: {
      state = match.step(keyState);
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
