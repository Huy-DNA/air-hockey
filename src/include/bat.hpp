#pragma once

#include <SDL_rect.h>
#include <SDL_render.h>

class Bat {
private:
  SDL_Texture *const sprite;
  SDL_Rect rect;

public:
  Bat(SDL_Texture *sprite, int x, int y, int s);
  void draw(SDL_Renderer *renderer) const;
  int getX() const;
  int getY() const;
  int getSize() const;
  void setX(int x);
  void setY(int y);
  void setSize(int size);
  void moveX(int disp, int capLeft, int capRight);
  void moveY(int disp, int capBottom, int capUp);
};
