#include "object/bat.hpp"
#include "object.hpp"
#include "vector2d.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

Bat::Bat(Sprite sprite, Vector2d pos, float radius)
    : Object{sprite, pos, Vector2d{0, 0}, Vector2d{0, 0}, 0}, _radius{radius} {}

bool Bat::doesCollide(const Puck &puck) const {
  const float dist = (puck.getPosition() - this->getPosition()).length();
  return dist < puck.getSize() + this->getSize();
}

float Bat::getSize() const { return _radius; }

void Bat::handleCollide(const Puck &puck) {
  }
