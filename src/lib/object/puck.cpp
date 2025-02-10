#include "object/puck.hpp"
#include "sprite.hpp"
#include "vector2d.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

Puck::Puck(Sprite sprite, Vector2d pos, float radius)
    : Object{sprite, pos, Vector2d{0, 0}, Vector2d{0, 0}, 0.1}, _radius{radius} {}

bool Puck::doesCollide(const Bat &bat) const { return bat.doesCollide(*this); }

float Puck::getSize() const { return _radius; }

void Puck::handleCollide(const Bat &bat) {
  if (!this->doesCollide(bat)) {
    return;
  }
  const Vector2d distVec = bat.getPosition() - this->getPosition();

  const float dist = distVec.length();
  const float sumRadius = bat.getSize() + this->getSize();
  const float diff = sumRadius - dist;

  this->setPosition(this->getPosition() + distVec.normalize() * diff);
}
