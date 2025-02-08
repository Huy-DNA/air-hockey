#pragma once

#include <SDL_render.h>
#include <SDL_video.h>
#include <string>

SDL_Surface *loadImage(const std::string path);
SDL_Texture *loadTexture(SDL_Renderer *renderer, const std::string path);
SDL_Rect createRect(int x, int y, int w, int h);
SDL_Window* createWindowOrFail(int w, int h);
SDL_Renderer* createRendererFromWindowOrFail(SDL_Window* window);
