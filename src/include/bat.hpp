#pragma once
#include <SDL_rect.h>
#include <SDL_render.h>

struct Bat {
  SDL_Texture *const sprite;
  SDL_Rect rect;
};

Bat createBat(SDL_Texture* sprite, SDL_Rect rect);

void draw(const Bat& bat, SDL_Renderer *renderer);
