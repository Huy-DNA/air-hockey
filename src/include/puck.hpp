#pragma once

#include <SDL_rect.h>
#include <SDL_render.h>

class Puck {
private:
  SDL_Texture *const sprite;
  SDL_Rect rect;

public:
  Puck(SDL_Texture *sprite, int x, int y, int s);
  void draw(SDL_Renderer *renderer) const;
  int getX() const;
  int getY() const;
  int getSize() const;
  void setX(int x);
  void setY(int y);
  void setSize(int s);
};
