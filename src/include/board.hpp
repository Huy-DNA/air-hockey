#pragma once

#include "box.hpp"
#include "piece.hpp"
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
  Vector2d getGoalCenter(Color color) const;
  Vector2d getInitBatPos(Color color, Ally ally) const;
  Vector2d getInitPuckPos() const;
  Vector2d getRandomBatPos(Color color) const;
  bool doesPuckCollideWithGoal(Color color, Puck &) const;
  void capBatPosition(Bat &) const;
  void capPuckPosition(Puck &) const;
};
