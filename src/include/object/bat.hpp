#pragma once

#include "box.hpp"
#include "object.hpp"
#include "object/puck.hpp"
#include "vector2d.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

class Puck;

class Bat : public Object {
private:
  float _radius;

public:
  Bat(Sprite sprite, Vector2d pos, float radius);
  bool doesCollide(const Puck &) const;
  Vector2d getCollisionPoint(const Puck &) const;
  float getSize() const;
};
