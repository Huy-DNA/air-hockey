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
void Bat::moveX(int disp, int capLeft, int capRight) {
  const int newX = this->getX() + disp;
  if (newX - rect.w / 2 < capLeft || newX + rect.w / 2 > capRight) {
    return;
  }
  this->setX(newX);
}
void Bat::moveY(int disp, int capUp, int capBottom) {
  const int newY = this->getY() + disp;
  if (newY + rect.h / 2 > capBottom || newY - rect.h / 2 < capUp) {
    return;
  }
  this->setY(newY);
}
void Bat::draw(SDL_Renderer *renderer) const {
  SDL_RenderCopy(renderer, sprite, NULL, &rect);
}
