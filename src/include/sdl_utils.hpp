#pragma once

#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <string>

SDL_Surface *loadImage(const std::string path);
SDL_Texture *loadTexture(SDL_Renderer *renderer, const std::string path);
SDL_Rect createRect(int x, int y, int w, int h);
SDL_Color createColor(int r, int g, int b, int a);
SDL_Window* createWindowOrFail(int w, int h);
SDL_Renderer* createRendererFromWindowOrFail(SDL_Window* window);
