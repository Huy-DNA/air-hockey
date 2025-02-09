#include "object.hpp"
#include "box.hpp"
#include "sdl_utils.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

Box::Box(SDL_Texture *sprite, int x, int y, int w, int h)
    : _sprite{sprite}, _x{x}, _y{y}, _w{w}, _h{h} {}
int Box::getLeft() const { return _x; }
int Box::getRight() const { return _x + _w; }
int Box::getBottom() const { return _y + _h; }
int Box::getUp() const { return _y; }
int Box::getWidth() const { return _w; }
int Box::getHeight() const { return _h; }
void Box::draw(SDL_Renderer* renderer) const {
  const SDL_Rect rect = createRect(_x, _y, _w, _h);
  SDL_RenderCopy(renderer, this->_sprite, NULL, &rect);
}
