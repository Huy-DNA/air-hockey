#include "board.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

Board Board::create(SDL_Texture *sprite, SDL_Rect rect) {
  return Board{sprite, rect};
}

void Board::draw(SDL_Renderer *renderer) const {
  SDL_RenderCopy(renderer, this->sprite, NULL, &this->rect);
}
