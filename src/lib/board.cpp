#include "board.hpp"
#include "object.hpp"
#include "vector2d.hpp"

Board::Board(SDL_Texture *sprite, int x, int y, int w, int h)
    : Box{sprite, x, y, w, h} {}
Board::Board(const Board &other)
    : Box{other._sprite, other._x, other._y, other._w, other._h} {}
Board &Board::operator=(const Board &other) {
  this->_sprite = other._sprite;
  this->_w = other._w;
  this->_h = other._h;
  this->_x = other._x;
  this->_y = other._y;
  return *this;
}

float Board::getGoalSize() const { return this->_h / 3.5; }

Vector2d Board::getBlueGoalCenter() const {
  return Vector2d{
      (float)_x,
      _y + _h / 2.0f,
  };
}

Vector2d Board::getRedGoalCenter() const {
  return Vector2d{
      (float)_x + _w,
      _y + _h / 2.0f,
  };
}

Vector2d Board::getInitBlueBatPos() const {
  return Vector2d{this->_x + this->_w / 9.0f, this->_y + this->_h / 2.0f};
}

Vector2d Board::getInitRedBatPos() const {
  return Vector2d{this->_x + this->_w * 8.0f / 9.0f,
                  this->_y + this->_h / 2.0f};
}

Vector2d Board::getInitPuckPos() const {
  return Vector2d{this->_x + this->_w / 2.0f, this->_y + this->_h / 2.0f};
}

void Board::capPuckPosition(Puck &puck) const {
  const Vector2d pos = puck.getPosition();
  float left = this->_x + puck.getSize();
  float right = this->_x + this->_w - puck.getSize();
  float bottom = this->_y + this->_h - puck.getSize();
  float up = this->_y + puck.getSize();

  if (pos.x < left) {
    puck.setXPosition(left);
  } else if (pos.x > right) {
    puck.setXPosition(right);
  }
  if (pos.y < up) {
    puck.setYPosition(up);
  } else if (pos.y > bottom) {
    puck.setYPosition(bottom);
  }
}

void Board::capBlueBatPosition(Bat &bat) const {
  const Vector2d pos = bat.getPosition();
  float left = this->_x + bat.getSize();
  float right = this->_x + this->_w / 2.0 - bat.getSize();
  float bottom = this->_y + this->_h - bat.getSize();
  float up = this->_y + bat.getSize();

  if (pos.x < left) {
    bat.setXPosition(left);
  } else if (pos.x > right) {
    bat.setXPosition(right);
  }
  if (pos.y < up) {
    bat.setYPosition(up);
  } else if (pos.y > bottom) {
    bat.setYPosition(bottom);
  }
}

void Board::capRedBatPosition(Bat &bat) const {
  const Vector2d pos = bat.getPosition();
  float left = this->_x + this->_w / 2.0 + bat.getSize();
  float right = this->_x + this->_w - bat.getSize();
  float bottom = this->_y + this->_h - bat.getSize();
  float up = this->_y + bat.getSize();

  if (pos.x < left) {
    bat.setXPosition(left);
  } else if (pos.x > right) {
    bat.setXPosition(right);
  }
  if (pos.y < up) {
    bat.setYPosition(up);
  } else if (pos.y > bottom) {
    bat.setYPosition(bottom);
  }
}

bool Board::doesPuckCollideWithBlueGoal(Puck &puck) const {
  const Vector2d pos = puck.getPosition();
  const Vector2d center = this->getBlueGoalCenter();
  const float goalSize = this->getGoalSize();
  if (puck.doesCollideLeft(*this) && pos.y <= center.y + goalSize &&
      pos.y >= center.y - goalSize) {
    return true;
  }
  return false;
}

bool Board::doesPuckCollideWithRedGoal(Puck &puck) const {
  const Vector2d pos = puck.getPosition();
  const Vector2d center = this->getRedGoalCenter();
  const float goalSize = this->getGoalSize();
  if (puck.doesCollideRight(*this) && pos.y <= center.y + goalSize &&
      pos.y >= center.y - goalSize) {
    return true;
  }
  return false;
}
