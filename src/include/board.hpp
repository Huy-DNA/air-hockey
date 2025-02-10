#pragma once

#include "box.hpp"
#include "object/bat.hpp"
#include "vector2d.hpp"
#include <SDL_rect.h>

class Bat;
class Puck;

class Board : public Box {
public:
  Board(SDL_Texture *sprite, int x, int y, int w, int h);
  Board(const Board&);
  Board& operator=(const Board&);

  float getGoalSize() const;
  Vector2d getBlueGoalCenter() const;
  Vector2d getRedGoalCenter() const;
  Vector2d getInitBlueBatPos() const;
  Vector2d getInitRedBatPos() const;
  Vector2d getInitPuckPos() const;
  bool doesPuckCollideWithBlueGoal(Puck &) const;
  bool doesPuckCollideWithRedGoal(Puck &) const;
  void capBlueBatPosition(Bat &) const;
  void capRedBatPosition(Bat &) const;
  void capPuckPosition(Puck &) const;
};
