#pragma once

#include "box.hpp"
#include "object.hpp"
#include "vector2d.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

class Bat : public Object {
private:
  float _radius;
public:
  Bat(Sprite sprite, Vector2d pos, float radius);
  virtual bool doesCollide(const Object &other) const override;
  float getSize() const;
};
