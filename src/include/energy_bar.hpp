#pragma once

#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>

class EnergyBar {
private:
  SDL_Rect _rect;
  float _percent;
  SDL_Color _color;

public:
  EnergyBar(SDL_Rect rect, SDL_Color color);
  void setPercent(float percent);
  void addPercent(float percent);
  void draw(SDL_Renderer*) const;
};
