#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_video.h>

class Game {
public:
  static constexpr int SCREEN_WIDTH = 1400;
  static constexpr int SCREEN_HEIGHT = 700;

  Game() {
    this->_window = SDL_CreateWindow("Air hockey", SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                     SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (this->_window == NULL) {
      printf("Window could not be created! Error: %s\n", SDL_GetError());
      exit(1);
    }
    this->_surface = SDL_GetWindowSurface(this->_window);
    SDL_FillRect(this->_surface, NULL,
                 SDL_MapRGB(this->_surface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(this->_window);

    this->_renderer =
        SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);
    if (this->_renderer == NULL) {
      printf("Renderer could not be created! Error: %s\n", SDL_GetError());
    }
  }

  ~Game() { SDL_DestroyWindow(this->_window); }

  void start() {
    bool quit = false;
    while (!quit) {
      SDL_Event e;
      while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }
      }
    }
  }

private:
  SDL_Window *_window;
  SDL_Surface *_surface;
  SDL_Renderer *_renderer;
};
