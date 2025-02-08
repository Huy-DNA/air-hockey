#include "board.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

void Board::draw(SDL_Renderer* renderer) const {
  SDL_RenderCopy(renderer, this->sprite, NULL, &this->rect);
}
