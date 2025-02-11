#pragma once

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
  Vector2d _acceleration;
  float _friction;

public:
  Object(Sprite sprite, Vector2d position, Vector2d velocity,
         Vector2d acceleration, float friction);

  void setPosition(const Vector2d pos);
  Vector2d getPosition() const;
  void setXPosition(const float x);
  void setYPosition(const float y);
  void setVelocity(const Vector2d v);
  void addVelocity(const Vector2d v);
  Vector2d getVelocity() const;
  void setAcceleration(const Vector2d a);
  void addAcceleration(const Vector2d a);
  Vector2d getAcceleration(const Vector2d a) const;
  void move(const float ms);
  void draw(SDL_Renderer *renderer) const;
};
