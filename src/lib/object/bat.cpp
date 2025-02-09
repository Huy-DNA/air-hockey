#include "object/bat.hpp"
#include "object.hpp"
#include "vector2d.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

Bat::Bat(Sprite sprite, Vector2d pos, float radius)
    : Object{sprite, pos, Vector2d{0, 0}}, _radius{radius} {}

bool Bat::doesCollide(const Object &other) const { throw "Unimplemented"; }
