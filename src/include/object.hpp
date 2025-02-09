#pragma once

#include "box.hpp"
#include "sprite.hpp"
#include "vector2d.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

class Box;

class Object {
private:
  Sprite _sprite;
  Vector2d _position;
  Vector2d _velocity;

public:
  Object(Sprite sprite, Vector2d position, Vector2d velocity);

  virtual bool doesCollide(const Object &other) const = 0;
  void setPosition(const Vector2d pos);
  Vector2d getPosition() const;
  void setXPosition(const float x);
  void setYPosition(const float y);
  void setVelocity(const Vector2d v);
  void addVelocity(const Vector2d v);
  Vector2d getVelocity() const;
  void move(const float ms);
  void draw(SDL_Renderer *renderer) const;
};
