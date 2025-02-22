#include "mousestate.hpp"
#include "vector2d.hpp"

void MouseState::setLeft(State state) {
  this->_prev_left_state = this->_current_left_state;
  this->_current_left_state = state;
}
void MouseState::setRight(State state) {
  this->_prev_right_state = this->_current_right_state;
  this->_current_right_state = state;
}
void MouseState::setPosition(Vector2d position) { this->_pos = position; }
bool MouseState::isLeftClicked() const {
  return this->_prev_left_state == UNPRESSED &&
         this->_current_left_state == PRESSED;
}
bool MouseState::isLeftUnclicked() const {
  return this->_prev_left_state == PRESSED &&
         this->_current_left_state == UNPRESSED;
}
bool MouseState::isLeftPressed() const {
  return this->_current_left_state == PRESSED;
}
bool MouseState::isLeftUnpressed() const { return !this->isLeftPressed(); }
bool MouseState::isRightClicked() const {
  return this->_prev_right_state == UNPRESSED &&
         this->_current_right_state == PRESSED;
}
bool MouseState::isRightUnclicked() const {
  return this->_prev_right_state == PRESSED &&
         this->_current_right_state == UNPRESSED;
}
bool MouseState::isRightPressed() const {
  return this->_current_right_state == PRESSED;
}
bool MouseState::isRightUnpressed() const { return !this->isRightPressed(); }
Vector2d MouseState::getPosition() const { return this->_pos; }
