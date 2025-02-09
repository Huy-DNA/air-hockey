#include "sprite.hpp"
#include "sdl_utils.hpp"
#include "vector2d.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

Sprite::Sprite(SDL_Texture *texture, Vector2d center, float w, float h)
    : _texture{texture}, _center{center}, _w{w}, _h{h} {}

void Sprite::draw(SDL_Renderer *renderer, Vector2d position) const {
  const SDL_Rect rect =
      createRect(position.x - _center.x, position.y - _center.y, _w, _h);
  SDL_RenderCopy(renderer, this->_texture, NULL, &rect);
}
