#include "sdl_utils.hpp"
#include <SDL_image.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <SDL_video.h>

SDL_Surface *loadImage(const std::string path) {
  return IMG_Load(path.c_str());
}

SDL_Texture *loadTexture(SDL_Renderer *renderer, const std::string path) {
  SDL_Surface *loadedSurface = loadImage(path);
  if (loadedSurface == NULL) {
    printf("Unable to load image %s! Error: %s\n", path.c_str(),
           IMG_GetError());
    return NULL;
  }
  SDL_Texture *newTexture =
      SDL_CreateTextureFromSurface(renderer, loadedSurface);
  if (newTexture == NULL) {
    printf("Unable to create texture from %s! Error: %s\n", path.c_str(),
           SDL_GetError());
  }

  SDL_FreeSurface(loadedSurface);

  return newTexture;
}

SDL_Rect createRect(int x, int y, int w, int h) {
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.h = h;
  rect.w = w;
  return rect;
}

SDL_Color createColor(int r, int g, int b, int a) {
  SDL_Color color;
  color.r = r;
  color.g = g;
  color.b = b;
  color.a = a;
  return color;
}

SDL_Window *createWindowOrFail(int w, int h) {
  SDL_Window *window =
      SDL_CreateWindow("Air hockey", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("Window could not be created! Error: %s\n", SDL_GetError());
    exit(1);
  }

  return window;
}

SDL_Renderer *createRendererFromWindowOrFail(SDL_Window *window) {
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("Renderer could not be created! Error: %s\n", SDL_GetError());
    exit(1);
  }
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  return renderer;
}

SDL_Texture *loadText(SDL_Renderer *renderer, TTF_Font *font, std::string text,
                      SDL_Color color) {
  SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
  if (textSurface == NULL) {
    printf("Unable to render text surface! SDL_ttf Error: %s\n",
           TTF_GetError());
    return NULL;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);
  if (texture == NULL) {
    printf("Unable to create texture from rendered text! SDL Error: %s\n",
           SDL_GetError());
  }
  SDL_FreeSurface(textSurface);
  return texture;
}

TTF_Font *loadFontOrFail(std::string path, int ptsize) {
  if (TTF_Init() < 0) {
    printf("Unable to init SDL_ttf! SDL_ttf Error: %s\n", TTF_GetError());
    exit(1);
  }
  TTF_Font *font = TTF_OpenFont(path.c_str(), ptsize);
  if (font == NULL) {
    printf("Unable to load font! SDL_ttf Error: %s\n", TTF_GetError());
    exit(1);
  }
  return font;
}
