#include "images.hpp"
#include <SDL_image.h>
#include <SDL_render.h>

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
