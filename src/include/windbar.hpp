#pragma once

#include "vector2d.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <cstdlib>

class WindBar {
private:
  float _wind_rate;
  Vector2d _position;
  SDL_Texture *_wind_left_texture;
  SDL_Texture *_wind_right_texture;
  TTF_Font *_font;

public:
  WindBar(SDL_Texture *wind_left, SDL_Texture *wind_right, TTF_Font *font,
          Vector2d pos);
  void setWindRate(float windRate);
  float getWindRate() const;
  Vector2d getWindVelocity() const;
  void draw(SDL_Renderer *renderer) const;
};
