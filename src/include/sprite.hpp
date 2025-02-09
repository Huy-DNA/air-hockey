#pragma once

#include "vector2d.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

struct Sprite {
private:
  SDL_Texture *_texture;
  Vector2d _center;
  float _w;
  float _h;
public:
  Sprite(SDL_Texture *texture, Vector2d center, float w, float h);
  void draw(SDL_Renderer* renderer, Vector2d position) const;
};
