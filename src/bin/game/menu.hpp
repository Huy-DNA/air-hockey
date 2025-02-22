#pragma once

#include "board.hpp"
#include "constants.hpp"
#include "object/bat.hpp"
#include "sdl_utils.hpp"
#include <SDL_pixels.h>
#include <SDL_render.h>

class MainMenu {
private:
  const inline static Board BOARD =
      Board(FIELD_TEXTURE, 0, 100, FIELD_WIDTH, FIELD_HEIGHT);
  const inline static SDL_Color BLACK_COLOR =
      createColor(0x00, 0x00, 0x00, 0xFF);
  const inline static SDL_Rect GAME_NAME_RECT =
      createRect(SCREEN_WIDTH / 2.0 - 180, 20, 360, 75);
  inline static SDL_Texture *GAME_NAME_TEXTURE =
      loadText(RENDERER, FONT, "Air Hockey", MainMenu::BLACK_COLOR);

  const inline static SDL_Color VIOLET_COLOR =
      createColor(0xA0, 0x20, 0xF0, 0xFF);
  const inline static SDL_Rect START_GAME_RECT =
      createRect(SCREEN_WIDTH / 2.0 - 60, SCREEN_HEIGHT / 2, 120, 50);
  inline static SDL_Texture *START_GAME_TEXTURE =
      loadText(RENDERER, FONT, "Start", MainMenu::VIOLET_COLOR);
  const inline static SDL_Rect INSTRUCTION_RECT =
      createRect(SCREEN_WIDTH / 2.0 - 120, SCREEN_HEIGHT / 2 + 75, 240, 50);
  inline static SDL_Texture *INSTRUCTION_TEXTURE =
      loadText(RENDERER, FONT, "Instruction", MainMenu::VIOLET_COLOR);

  const inline static Bat BLUE_BAT =
      Bat(BAT_BLUE_SPRITE, Color::BLUE,
          {SCREEN_WIDTH / 2.0 - 180 - BAT_SIZE / 2.0 - 10, 50}, BAT_SIZE / 2.0);

  const inline static Bat RED_BAT =
      Bat(BAT_RED_SPRITE, Color::RED,
          {SCREEN_WIDTH / 2.0 + 180 + BAT_SIZE / 2.0 + 10, 50}, BAT_SIZE / 2.0);

public:
  void draw() const {
    SDL_SetRenderDrawColor(RENDERER, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(RENDERER);

    MainMenu::BOARD.draw(RENDERER);

    BLUE_BAT.draw(RENDERER);
    RED_BAT.draw(RENDERER);

    SDL_RenderCopy(RENDERER, MainMenu::START_GAME_TEXTURE, NULL,
                   &MainMenu::START_GAME_RECT);

    SDL_RenderCopy(RENDERER, MainMenu::INSTRUCTION_TEXTURE, NULL,
                   &MainMenu::INSTRUCTION_RECT);

    SDL_RenderCopy(RENDERER, MainMenu::GAME_NAME_TEXTURE, NULL,
                   &MainMenu::GAME_NAME_RECT);

    SDL_RenderPresent(RENDERER);
  }
};
