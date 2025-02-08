#pragma once

#include "constants.hpp"
#include "images.hpp"
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_video.h>

class Game {
public:
  static constexpr int SCREEN_WIDTH = 1400;
  static constexpr int SCREEN_HEIGHT = 700;

  Game() {
    this->_window = SDL_CreateWindow("Air hockey", SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                     SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (this->_window == NULL) {
      printf("Window could not be created! Error: %s\n", SDL_GetError());
      exit(1);
    }

    this->_renderer =
        SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);
    if (this->_renderer == NULL) {
      printf("Renderer could not be created! Error: %s\n", SDL_GetError());
      exit(1);
    }
    SDL_SetRenderDrawColor(this->_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(this->_renderer);
    SDL_RenderPresent(this->_renderer);

    this->_icon = loadImage(BAT_BLUE_SPRITE_PATH);
    SDL_SetWindowIcon(this->_window, this->_icon);

    this->_puck_texture = loadTexture(this->_renderer, PUCK_SPRITE_PATH);
    this->_bat_blue_texture =
        loadTexture(this->_renderer, BAT_BLUE_SPRITE_PATH);
    this->_bat_red_texture =
        loadTexture(this->_renderer, BAT_RED_SPRITE_PATH);
    this->_field_texture =
        loadTexture(this->_renderer, FIELD_SPRITE_PATH);
  }

  ~Game() {
   SDL_FreeSurface(this->_icon);
   SDL_DestroyTexture(this->_puck_texture);
   SDL_DestroyTexture(this->_field_texture);
   SDL_DestroyTexture(this->_bat_red_texture);
   SDL_DestroyTexture(this->_bat_blue_texture);
   SDL_DestroyRenderer(this->_renderer);
   SDL_DestroyWindow(this->_window);
  }

  void start() {
    bool quit = false;
    while (!quit) {
      SDL_Event e;
      while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }
      }
    }
  }

private:
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  SDL_Surface *_icon;

  SDL_Texture *_puck_texture;
  SDL_Texture *_bat_blue_texture;
  SDL_Texture *_bat_red_texture;
  SDL_Texture *_field_texture;
};
