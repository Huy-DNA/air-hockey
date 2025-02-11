#pragma once

#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>

class EnergyBar {
private:
  SDL_Rect _rect;
  SDL_Color _color;
  float _cur_percent;
  float _target_percent;
  float _percent_per_ms;

public:
  EnergyBar(SDL_Rect rect, SDL_Color color, float percentPerMs);
  void setPercent(float percent);
  void addPercent(float percent);
  void draw(SDL_Renderer*, unsigned long long deltaMs);
  bool isFull() const;
};
