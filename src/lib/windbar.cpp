#include "windbar.hpp"
#include "sdl_utils.hpp"
#include "vector2d.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <cstdlib>
#include <stdexcept>

WindBar::WindBar(SDL_Texture *wind_left, SDL_Texture *wind_right,
                 TTF_Font *font, Vector2d pos)
    : _wind_left_texture{wind_left}, _wind_right_texture{wind_right},
      _font{font}, _position{pos}, _wind_rate{0} {};
void WindBar::setWindRate(float windRate) {
  if (windRate < -1 || windRate > 1) {
    throw std::invalid_argument("Wind rate should be in [-1, 1]");
  }
  this->_wind_rate = (int)(windRate * 10) / 10.0;
}
float WindBar::getWindRate() const { return this->_wind_rate; }
Vector2d WindBar::getWindVelocity() const {
  return Vector2d{this->_wind_rate, 0};
}
void WindBar::draw(SDL_Renderer *renderer) const {
  const SDL_Rect numberRect =
      createRect(_position.x - 30, _position.y - 25, 60, 75);
  SDL_Texture *text = loadText(
      renderer, this->_font, std::to_string(abs((int)(this->_wind_rate * 10))),
      createColor(0x63, 0xC5, 0xDA, 0xFF));
  SDL_RenderCopy(renderer, text, NULL, &numberRect);
  SDL_DestroyTexture(text);
  if (this->_wind_rate < 0) {
    const SDL_Rect leftRect =
        createRect(_position.x - 110, _position.y - 30, 70, 75);
    SDL_RenderCopy(renderer, this->_wind_left_texture, NULL, &leftRect);
  }
  if (this->_wind_rate > 0) {
    const SDL_Rect rightRect =
        createRect(_position.x + 40, _position.y - 30, 70, 75);
    SDL_RenderCopy(renderer, this->_wind_right_texture, NULL, &rightRect);
  }
}
