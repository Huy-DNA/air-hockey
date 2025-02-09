#pragma once

struct Vector2d {
  float x;
  float y;
  Vector2d operator+(const Vector2d&) const;
  Vector2d operator+() const;
  Vector2d operator-(const Vector2d&) const;
  Vector2d operator-() const;
  Vector2d operator*(const float) const;
  Vector2d operator/(const float) const;
  Vector2d normalize() const;
  float length() const;
};
