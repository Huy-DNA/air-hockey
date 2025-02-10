#pragma once

#include "object.hpp"
#include "object/bat.hpp"
#include "board.hpp"
#include "sprite.hpp"
#include "vector2d.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

class Board;
class Bat;

class Puck : public Object {
private:
  float _radius;

public:
  Puck(Sprite sprite, Vector2d pos, float radius);
  bool doesCollide(const Bat &) const;
  bool doesCollideLeft(const Board &) const;
  bool doesCollideRight(const Board &) const;
  bool doesCollideUp(const Board &) const;
  bool doesCollideDown(const Board &) const;
  Vector2d getCollisionPoint(const Bat &) const;
  float getSize() const;
  void setVelocity(const Vector2d v);
};
