#include "object/puck.hpp"
#include "sprite.hpp"
#include "vector2d.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

Puck::Puck(Sprite sprite, Vector2d pos, float radius)
    : Object{sprite, pos, Vector2d{0, 0}, Vector2d{0, 0}, 0.05},
      _radius{radius} {}

bool Puck::doesCollide(const Bat &bat) const { return bat.doesCollide(*this); }

bool Puck::doesCollideLeft(const Board &board) const {
  return this->getPosition().x - this->_radius <= board.getLeft();
}
bool Puck::doesCollideRight(const Board &board) const {
  return this->getPosition().x + this->_radius >= board.getRight();
}
bool Puck::doesCollideUp(const Board &board) const {
  return this->getPosition().y - this->_radius <= board.getUp();
}
bool Puck::doesCollideDown(const Board &board) const {
  return this->getPosition().y + this->_radius >= board.getBottom();
}

void Puck::setVelocity(const Vector2d v) {
  this->Object::setVelocity(v.cap(1));
}

float Puck::getSize() const { return _radius; }

Vector2d Puck::getCollisionPoint(const Bat &bat) const {
  return bat.getCollisionPoint(*this);
}
