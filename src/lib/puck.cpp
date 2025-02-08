#include "puck.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

Puck::Puck(SDL_Texture *sprite, int x, int y, int s) : sprite{sprite}, rect{} {
  this->setSize(s);
  this->setX(x);
  this->setY(y);
}
int Puck::getX() const { return rect.x + rect.w / 2; }
int Puck::getY() const { return rect.y + rect.h / 2; }
int Puck::getSize() const { return rect.w; };
void Puck::setX(int x) { rect.x = x - rect.w / 2; }
void Puck::setY(int y) { rect.y = y - rect.h / 2; }
void Puck::setSize(int s) { rect.h = rect.w = s; }
void Puck::draw(SDL_Renderer *renderer) const {
  SDL_RenderCopy(renderer, sprite, NULL, &rect);
}
