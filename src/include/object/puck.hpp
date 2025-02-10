#pragma once

#include "object.hpp"
#include "object/bat.hpp"
#include "sprite.hpp"
#include "vector2d.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

class Bat;

class Puck : public Object {
private:
  float _radius;
public:
  Puck(Sprite sprite, Vector2d pos, float radius);
  bool doesCollide(const Bat &) const;
  float getSize() const;
};
