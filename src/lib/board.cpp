#include "board.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

void draw(const Board& board, SDL_Renderer *renderer) {
  SDL_RenderCopy(renderer, board.sprite, NULL, &board.rect);
}

Board createBoard(SDL_Texture* sprite, SDL_Rect rect) {
  return Board{sprite, rect};
}
