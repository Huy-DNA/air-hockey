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
