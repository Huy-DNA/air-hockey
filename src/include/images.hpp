#pragma once

#include <SDL_render.h>
#include <string>

SDL_Surface *loadImage(const std::string path);
SDL_Texture *loadTexture(SDL_Renderer *renderer, const std::string path);
