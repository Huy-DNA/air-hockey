#include "board.hpp"
#include "object.hpp"
#include "vector2d.hpp"

Board::Board(SDL_Texture *sprite, int x, int y, int w, int h)
    : Box{sprite, x, y, w, h} {}

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

void Board::capPosition(Object &obj) const {
  const Vector2d pos = obj.getPosition();
  if (pos.x < this->_x) {
    obj.setXPosition(this->_x);
  } else if (pos.x > this->_x + this->_w) {
    obj.setXPosition(this->_x + this->_w);
  }
  if (pos.y < this->_y) {
    obj.setYPosition(this->_y);
  } else if (pos.y > this->_y + this->_h) {
    obj.setYPosition(this->_y + this->_h);
  }
}

void Board::capBlueBatPosition(Bat &bat) const {
  const Vector2d pos = bat.getPosition();
  float left = this->_x;
  float right = this->_x + this->_w / 2.0;
  float bottom = this->_y + this->_h;
  float up = this->_y;

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
  float left = this->_x + this->_w / 2.0;
  float right = this->_x + this->_w;
  float bottom = this->_y + this->_h;
  float up = this->_y;

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
