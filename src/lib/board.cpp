#include "board.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

Board::Board(SDL_Texture *sprite, int x, int y, int w, int h) : sprite{sprite}, rect{} {
  this->setX(x);
  this->setY(y);
  this->setWidth(w);
  this->setHeight(h);
}
void Board::draw(SDL_Renderer *renderer) const {
  SDL_RenderCopy(renderer, sprite, NULL, &rect);
}
int Board::getWidth() const { return rect.w; }
int Board::getHeight() const { return rect.h; }
int Board::getX() const { return rect.x; }
int Board::getY() const { return rect.y; }
void Board::setX(int x) { rect.x = x; }
void Board::setY(int y) { rect.y = y; }
void Board::setWidth(int w) { rect.w = w; }
void Board::setHeight(int h) { rect.h = h; }
int Board::getBlueBatInitX() const { return rect.x + 11 * rect.w / 100; }
int Board::getBlueBatInitY() const { return rect.y + rect.h / 2; }
int Board::getRedBatInitX() const { return rect.x + 89 * rect.w / 100; }
int Board::getRedBatInitY() const { return rect.y + rect.h / 2; }
