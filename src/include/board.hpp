#pragma once
#include <SDL_rect.h>
#include <SDL_render.h>

class Board {
private:
  SDL_Texture *const sprite;
  SDL_Rect rect;

public:
  Board(SDL_Texture *sprite, int x, int y, int w, int h);
  void draw(SDL_Renderer *renderer) const;
  int getWidth() const;
  int getHeight() const;
  int getX() const;
  int getY() const;
  void setX(int x);
  void setY(int y);
  void setWidth(int w);
  void setHeight(int h);
  int getBlueBatInitX() const;
  int getBlueBatInitY() const;
  int getRedBatInitX() const;
  int getRedBatInitY() const;
};
