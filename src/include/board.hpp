#pragma once
#include <SDL_rect.h>
#include <SDL_render.h>

struct Board {
  SDL_Texture *const sprite;
  const SDL_Rect rect;
};

void draw(const Board& board, SDL_Renderer *renderer);
Board createBoard(SDL_Texture* sprite, SDL_Rect rect);
