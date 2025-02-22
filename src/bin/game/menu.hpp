#pragma once

#include "board.hpp"
#include "button.hpp"
#include "constants.hpp"
#include "mousestate.hpp"
#include "object/bat.hpp"
#include "sdl_utils.hpp"
#include "state.hpp"
#include <SDL_pixels.h>
#include <SDL_render.h>

class MainMenu {
private:
  const inline static Board BOARD =
      Board(FIELD_TEXTURE, 0, 100, FIELD_WIDTH, FIELD_HEIGHT);

  const inline static SDL_Color WHITE_COLOR =
      createColor(0xFF, 0xFF, 0xFF, 0xFF);
  const inline static SDL_Color BLACK_COLOR =
      createColor(0x00, 0x00, 0x00, 0xFF);
  const inline static SDL_Color VIOLET_COLOR =
      createColor(0xA0, 0x20, 0xF0, 0xFF);

  const inline static SDL_Rect GAME_NAME_RECT =
      createRect(SCREEN_WIDTH / 2.0 - 180, 20, 360, 75);
  inline static SDL_Texture *GAME_NAME_TEXTURE =
      loadText(RENDERER, FONT, "Air Hockey", MainMenu::BLACK_COLOR);

  const inline static Button START_GAME_BUTTON = Button(
      MainMenu::VIOLET_COLOR, MainMenu::WHITE_COLOR, FONT,
      createRect(SCREEN_WIDTH / 2.0 - 60, SCREEN_HEIGHT / 2, 120, 50), "Start");
  const inline static Button INSTRUCTION_BUTTON = Button(
      MainMenu::VIOLET_COLOR, MainMenu::WHITE_COLOR, FONT,
      createRect(SCREEN_WIDTH / 2.0 - 120, SCREEN_HEIGHT / 2 + 75, 240, 50),
      "Instruction");

  const inline static Bat BLUE_BAT =
      Bat(BAT_BLUE_SPRITE, Color::BLUE,
          {SCREEN_WIDTH / 2.0 - 180 - BAT_SIZE / 2.0 - 10, 50}, BAT_SIZE / 2.0);

  const inline static Bat RED_BAT =
      Bat(BAT_RED_SPRITE, Color::RED,
          {SCREEN_WIDTH / 2.0 + 180 + BAT_SIZE / 2.0 + 10, 50}, BAT_SIZE / 2.0);

public:
  GameState step(const MouseState& mouseState) const {
    if (START_GAME_BUTTON.isClicked(mouseState)) {
      return GameState::START_MATCH;
    }

    if (INSTRUCTION_BUTTON.isClicked(mouseState)) {
      return GameState::INSTRUCTION;
    }

    SDL_SetRenderDrawColor(RENDERER, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(RENDERER);

    MainMenu::BOARD.draw(RENDERER);

    BLUE_BAT.draw(RENDERER);
    RED_BAT.draw(RENDERER);

    START_GAME_BUTTON.draw(RENDERER);
    INSTRUCTION_BUTTON.draw(RENDERER);

    SDL_RenderCopy(RENDERER, MainMenu::GAME_NAME_TEXTURE, NULL,
                   &MainMenu::GAME_NAME_RECT);

    SDL_RenderPresent(RENDERER);

    return GameState::MAIN_MENU;
  }
};
