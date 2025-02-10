#pragma once

#include <SDL_rect.h>
#include <SDL_render.h>

class Object;

class Box {
protected:
  SDL_Texture * _sprite;
  int _x;
  int _y;
  int _w;
  int _h;

public:
  Box(SDL_Texture *sprite, int x, int y, int w, int h);

  int getLeft() const;
  int getRight() const;
  int getBottom() const;
  int getUp() const;
  int getWidth() const;
  int getHeight() const;
  
  void draw(SDL_Renderer*) const;
};
