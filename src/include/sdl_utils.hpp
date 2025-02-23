#pragma once

#include <SDL_mixer.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <SDL_video.h>
#include <string>

void initSDL();
void finalizeSDL();
SDL_Surface *loadImage(const std::string path);
SDL_Texture *loadTexture(SDL_Renderer *renderer, const std::string path);
SDL_Texture *loadText(SDL_Renderer *renderer, TTF_Font *font, std::string text,
                      SDL_Color color);
SDL_Rect createRect(int x, int y, int w, int h);
SDL_Color createColor(int r, int g, int b, int a);
SDL_Window *createWindowOrFail(int w, int h);
SDL_Renderer *createRendererFromWindowOrFail(SDL_Window *window);
TTF_Font* loadFontOrFail(std::string path, int ptsize);
Mix_Chunk* loadMixerChunkOrFail(std::string path);
