#include "constants.hpp"
#include "instruction.hpp"
#include "keystate.hpp"
#include "match.hpp"
#include "menu.hpp"
#include "mousestate.hpp"
#include "sdl_utils.hpp"
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
#include <cstdlib>

int main(int argc, const char *argv[]) { 
  initSDL();

  SDL_SetWindowIcon(WINDOW, ICON_SURFACE);

  KeyState keyState;
  MouseState mouseState;
  MainMenu menu;
  Instruction instruction;
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
      state = instruction.step(mouseState);
      break;
    }
    case GameState::START_MATCH: {
      match.hardReset();
      state = GameState::IN_MATCH;
      break;
    }
    case GameState::CONTINUE_MATCH: {
      match.softReset();
      state = GameState::IN_MATCH;
      break;
    }
    case GameState::IN_MATCH: {
      state = match.step(keyState, mouseState);
      break;
    }
    case GameState::QUIT: {
      goto quit;
    }
    }
  }
quit:

  finalizeSDL();
}
