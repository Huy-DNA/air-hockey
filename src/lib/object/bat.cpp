#include "object/bat.hpp"
#include "object.hpp"
#include "piece.hpp"
#include "vector2d.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

Bat::Bat(Sprite sprite, Color color, Vector2d pos, float radius)
    : Object{sprite, pos, Vector2d{0, 0}, Vector2d{0, 0}, 0}, _radius{radius},
      _color{color} {}

bool Bat::doesCollide(const Puck &puck) const {
  const float dist = (puck.getPosition() - this->getPosition()).length();
  return dist < puck.getSize() + this->getSize();
}

bool Bat::doesCollide(const Bat &bat) const {
  const float dist = (bat.getPosition() - this->getPosition()).length();
  return dist < bat.getSize() + this->getSize();
}

float Bat::getSize() const { return _radius; }

Color Bat::getColor() const { return this->_color; }

Vector2d Bat::getCollisionPoint(const Puck &puck) const {
  const Vector2d distVec =
      (puck.getPosition() - this->getPosition()).normalize();
  return this->getPosition() + distVec * this->_radius;
}
