#include "animation/energy_bar.hpp"
#include "sdl_utils.hpp"
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <cstdio>
#include <stdexcept>

EnergyBar::EnergyBar(SDL_Rect rect, SDL_Color color, float percentPerMs)
    : _rect{rect}, _cur_percent{0}, _target_percent{0}, _color{color},
      _percent_per_ms{percentPerMs} {};

void EnergyBar::setPercent(float percent) {
  if (percent < 0 || percent > 1) {
    throw new std::runtime_error("Out-of-bound percent");
  }
  this->_target_percent = percent;
}

void EnergyBar::addPercent(float percent) {
  float newPercent = this->_target_percent + percent;
  if (newPercent < 0) {
    newPercent = 0;
  }
  if (newPercent > 1) {
    newPercent = 1;
  }
  this->_target_percent = newPercent;
}

void EnergyBar::draw(SDL_Renderer *renderer, unsigned long long deltaMs) {
  const float diff = this->_target_percent - this->_cur_percent;
  if (diff != 0) {
    this->_cur_percent = this->_cur_percent - (diff < 0 ? 1 : -1) * this->_percent_per_ms * deltaMs;
    if (diff < 0 && this->_cur_percent < this->_target_percent) {
      this->_cur_percent = this->_target_percent;
    } else if (diff > 0 && this->_cur_percent > this->_target_percent) {
      this->_cur_percent = this->_target_percent;
    }
  }
  const float w = this->_cur_percent * this->_rect.w;
  SDL_Rect percentRect =
      createRect(this->_rect.x, this->_rect.y, w, this->_rect.h);
  SDL_SetRenderDrawColor(renderer, this->_color.r, this->_color.g,
                         this->_color.b, this->_color.a);
  SDL_RenderFillRect(renderer, &percentRect);
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &this->_rect);
}

bool EnergyBar::isFull() const { return this->_target_percent == 1; }
