#pragma once

#include "vector2d.hpp"

class MouseState {
public:
  enum State {
    PRESSED,
    UNPRESSED,
  };
private: 
  State _prev_left_state = UNPRESSED;
  State _current_left_state = UNPRESSED;
  State _prev_right_state = UNPRESSED;
  State _current_right_state = UNPRESSED;
  Vector2d _pos;
public:
  void setLeft(State);
  void setRight(State);
  void setPosition(Vector2d);
  Vector2d getPosition() const;
  bool isLeftClicked() const;
  bool isLeftUnclicked() const;
  bool isLeftPressed() const;
  bool isLeftUnpressed() const;
  bool isRightClicked() const;
  bool isRightUnclicked() const;
  bool isRightPressed() const;
  bool isRightUnpressed() const;
};
