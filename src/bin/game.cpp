#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cstdio>

constexpr int SCREEN_WIDTH = 1400;
constexpr int SCREEN_HEIGHT = 700;

void init();
void finalize();
static SDL_Window *g_window = NULL;
static SDL_Surface *g_surface = NULL;

int main(int argc, const char *argv[]) {
  init();

  bool quit = false;
  while (!quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
  }

  finalize();
}

void init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    exit(1);
  }

  g_window = SDL_CreateWindow("Air hockey", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (g_window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    exit(1);
  }
  g_surface = SDL_GetWindowSurface(g_window);
  SDL_FillRect(g_surface, NULL,
               SDL_MapRGB(g_surface->format, 0xFF, 0xFF, 0xFF));
  SDL_UpdateWindowSurface(g_window);
}

void finalize() {
  SDL_DestroyWindow(g_window);
  SDL_Quit();
}
