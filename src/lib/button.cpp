#include "button.hpp"
#include "sdl_utils.hpp"
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>

Button::Button(SDL_Color text_color, SDL_Color background_color, TTF_Font *font,
               SDL_Rect rect, const std::string &text)
    : _text_color{text_color}, _background_color{background_color}, _rect{rect},
      _font{font}, _text{text} {}

void Button::draw(SDL_Renderer *renderer) const {
  SDL_SetRenderDrawColor(renderer, this->_background_color.r,
                         this->_background_color.g, this->_background_color.b,
                         this->_background_color.a);
  SDL_RenderFillRect(renderer, &this->_rect);

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &this->_rect);

  SDL_Texture *text_texture =
      loadText(renderer, this->_font, this->_text, this->_text_color);
  SDL_Rect text_rect = createRect(this->_rect.x + 10, this->_rect.y + 10,
                                  this->_rect.w - 20, this->_rect.h - 20);
  SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
  SDL_DestroyTexture(text_texture);
}
