#include "energy_bar.hpp"
#include "sdl_utils.hpp"
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <cstdio>
#include <stdexcept>

EnergyBar::EnergyBar(SDL_Rect rect, SDL_Color color)
    : _rect{rect}, _percent{0}, _color{color} {};

void EnergyBar::setPercent(float percent) {
  if (percent < 0 || percent > 100) {
    throw new std::runtime_error("Out-of-bound percent");
  }
  this->_percent = percent;
}

void EnergyBar::addPercent(float percent) {
  this->_percent += percent;
  if (this->_percent < 0) {
    this->_percent = 0;
  }
  if (this->_percent > 100) {
    this->_percent = 100;
  }
}

void EnergyBar::draw(SDL_Renderer *renderer) const {
  const float w = this->_percent / 100.0 * this->_rect.w;
  SDL_Rect percentRect =
      createRect(this->_rect.x, this->_rect.y, w, this->_rect.h);
  SDL_SetRenderDrawColor(renderer, this->_color.r, this->_color.g,
                         this->_color.b, this->_color.a);
  SDL_RenderFillRect(renderer, &percentRect);
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &this->_rect);
}

bool EnergyBar::isFull() const {
  return this->_percent == 100;
}
