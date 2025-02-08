#pragma once
#include <SDL_rect.h>
#include <SDL_render.h>

struct Board {
  SDL_Texture *const sprite;
  const SDL_Rect rect;
  static Board create(SDL_Texture* sprite, SDL_Rect rect);
  void draw(SDL_Renderer *renderer) const;
};
