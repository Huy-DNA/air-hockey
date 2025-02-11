#pragma once

#include "constants.hpp"
#include "sdl_utils.hpp"
#include "vector2d.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>
#include <cstdlib>
#include <stdexcept>

class WindBar {
private:
  float _wind_rate;
  Vector2d _position;

public:
  WindBar(Vector2d pos) : _position{pos}, _wind_rate{0} {};
  void setWindRate(float windRate) {
    if (windRate < -1 || windRate > 1) {
      throw std::invalid_argument("Wind rate should be in [-1, 1]");
    }
    this->_wind_rate = (int)(windRate * 10) / 10.0;
  }
  float getWindRate() const { return this->_wind_rate; }
  Vector2d getWindVelocity() const { return Vector2d{this->_wind_rate, 0}; }
  void draw(SDL_Renderer *renderer) const {
    const SDL_Rect numberRect =
        createRect(_position.x - 30, _position.y - 25, 60, 75);
    SDL_RenderCopy(renderer,
                   loadText(renderer, FONT,
                            std::to_string(abs((int)(this->_wind_rate * 10))),
                            createColor(0x63, 0xC5, 0xDA, 0xFF)),
                   NULL, &numberRect);
    if (this->_wind_rate < 0) {
      const SDL_Rect leftRect =
          createRect(_position.x - 110, _position.y - 30, 70, 75);
      SDL_RenderCopy(renderer, WIND_LEFT_TEXTURE, NULL, &leftRect);
    }
    if (this->_wind_rate > 0) {
      const SDL_Rect rightRect =
          createRect(_position.x + 40, _position.y - 30, 70, 75);
      SDL_RenderCopy(renderer, WIND_RIGHT_TEXTURE, NULL, &rightRect);
    }
  }
};
