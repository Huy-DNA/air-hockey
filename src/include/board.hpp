#pragma once

#include "box.hpp"
#include "object/bat.hpp"
#include "vector2d.hpp"

class Bat;
class Puck;

class Board : public Box {
public:
  Board(SDL_Texture *sprite, int x, int y, int w, int h);

  Vector2d getInitBlueBatPos() const;
  Vector2d getInitRedBatPos() const;
  Vector2d getInitPuckPos() const;
  void capBlueBatPosition(Bat &) const;
  void capRedBatPosition(Bat &) const;
  void capPuckPosition(Puck &) const;
};
