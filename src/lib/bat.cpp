#include "bat.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

Bat createBat(SDL_Texture *sprite, SDL_Rect rect) {
  return Bat{
      sprite,
      rect,
  };
}

void draw(const Bat& bat, SDL_Renderer *renderer) {
  SDL_RenderCopy(renderer, bat.sprite, NULL, &bat.rect);
}
