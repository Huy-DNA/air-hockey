#pragma once

#include "object.hpp"
#include "sprite.hpp"
#include "vector2d.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

class Puck : public Object {
private:
  float _radius;
public:
  Puck(Sprite sprite, Vector2d pos, float radius);
  virtual bool doesCollide(const Object &other) const override;
  float getSize() const;
};
