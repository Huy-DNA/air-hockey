#pragma once

#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_ttf.h>
#include <string>

class Button {
private:
  const SDL_Color _text_color;
  const SDL_Color _background_color;
  const SDL_Rect _rect;
  const std::string _text;
  TTF_Font *const _font;

public:
  Button(SDL_Color text_color, SDL_Color background_color, TTF_Font *font,
         SDL_Rect rect, const std::string &text);
  void draw(SDL_Renderer *renderer) const;
};
