#include "bat.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

Bat::Bat(SDL_Texture *sprite, int x, int y, int s) : sprite{sprite}, rect{} {
  this->setSize(s);
  this->setX(x);
  this->setY(y);
}
int Bat::getX() const { return rect.x + rect.w / 2; }
int Bat::getY() const { return rect.y + rect.h / 2; }
int Bat::getSize() const { return rect.w; };
void Bat::setX(int x) { rect.x = x - rect.w / 2; }
void Bat::setY(int y) { rect.y = y - rect.h / 2; }
void Bat::setSize(int s) { rect.h = rect.w = s; }
void Bat::draw(SDL_Renderer *renderer) const {
  SDL_RenderCopy(renderer, sprite, NULL, &rect);
}
