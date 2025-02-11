#pragma once

#include "box.hpp"
#include "piece.hpp"
#include "object.hpp"
#include "object/puck.hpp"
#include "vector2d.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

class Puck;
class Board;

class Bat : public Object {
private:
  float _radius;
  Color _color;

public:
  Bat(Sprite sprite, Color color, Vector2d pos, float radius);
  bool doesCollide(const Puck &) const;
  bool doesCollide(const Bat &) const;
  Vector2d getCollisionPoint(const Puck &) const;
  float getSize() const;
  Color getColor() const;
};
