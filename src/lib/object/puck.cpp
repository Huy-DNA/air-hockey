#include "object/puck.hpp"
#include "sprite.hpp"
#include "vector2d.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

Puck::Puck(Sprite sprite, Vector2d pos, float radius)
    : Object{sprite, pos, Vector2d{0, 0}}, _radius{radius} {}

bool Puck::doesCollide(const Object &other) const { throw "Unimplemented"; }

float Puck::getSize() const { return _radius; }
