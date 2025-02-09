#include "vector2d.hpp"
#include <cmath>

Vector2d Vector2d::operator+(const Vector2d &other) const {
  return Vector2d{
      this->x + other.x,
      this->y + other.y,
  };
}

Vector2d Vector2d::operator+() const { return *this; }

Vector2d Vector2d::operator-(const Vector2d &other) const {
  return Vector2d{
      this->x - other.x,
      this->y - other.y,
  };
}

Vector2d Vector2d::operator-() const {
  return Vector2d{
      -this->x,
      -this->y,
  };
}

Vector2d Vector2d::operator*(const float c) const {
  return Vector2d{
      this->x * c,
      this->y * c,
  };
}

Vector2d Vector2d::operator/(const float c) const {
  return Vector2d{
      this->x / c,
      this->y / c,
  };
}

Vector2d Vector2d::normalize() const {
  const float length = this->length();
  return *this / length;
}

float Vector2d::length() const {
  return sqrt(this->x * this->x + this->y * this->y);
}
