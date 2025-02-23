#pragma once

#include "board.hpp"
#include "button.hpp"
#include "constants.hpp"
#include "mousestate.hpp"
#include "sdl_utils.hpp"
#include "state.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

class Instruction {
private:
  const inline static Button MENU_BUTTON = Button(
      createColor(0x00, 0x00, 0x00, 0xFF), createColor(0x00, 0xFF, 0xFF, 0xFF),
      FONT, createRect(SCREEN_WIDTH / 2 + 300, 25, 100, 50), "MENU");

  const inline static Board BOARD =
      Board(FIELD_TEXTURE, 0, 100, FIELD_WIDTH, FIELD_HEIGHT);
  const inline static Bat BLUE_BAT =
      Bat(BAT_BLUE_SPRITE, Color::BLUE,
          {SCREEN_WIDTH / 2.0 - 180 - BAT_SIZE / 2.0 - 10, 50}, BAT_SIZE / 2.0);

  const inline static Bat RED_BAT =
      Bat(BAT_RED_SPRITE, Color::RED,
          {SCREEN_WIDTH / 2.0 + 180 + BAT_SIZE / 2.0 + 10, 50}, BAT_SIZE / 2.0);

  const inline static SDL_Color WHITE_COLOR =
      createColor(0xFF, 0xFF, 0xFF, 0xFF);
  const inline static SDL_Color BLACK_COLOR =
      createColor(0x00, 0x00, 0x00, 0xFF);
  const inline static SDL_Color BLUE_COLOR =
      createColor(0x00, 0x00, 0xFF, 0xFF);
  const inline static SDL_Color RED_COLOR = createColor(0xFF, 0x00, 0x00, 0xFF);
  const inline static SDL_Color VIOLET_COLOR =
      createColor(0xA0, 0x20, 0xF0, 0xFF);

  const inline static SDL_Rect INSTRUCTION_RECT =
      createRect(SCREEN_WIDTH / 2.0 - 180, 20, 360, 75);
  inline static SDL_Texture *INSTRUCTION_TEXTURE =
      loadText(RENDERER, FONT, "Instruction", Instruction::BLACK_COLOR);

  const inline static SDL_Rect BACKGROUND_RECT =
      createRect(SCREEN_WIDTH / 8.0 - 100, SCREEN_HEIGHT / 8.0 + 50,
                 SCREEN_WIDTH * 6.0 / 8.0 + 200, SCREEN_HEIGHT * 6.0 / 8.0);

  const inline static SDL_Rect W_RECT =
      createRect(SCREEN_WIDTH / 8.0, SCREEN_HEIGHT / 8.0 + 100, 50, 50);
  const inline static SDL_Rect A_RECT =
      createRect(SCREEN_WIDTH / 8.0 + 55, SCREEN_HEIGHT / 8.0 + 100, 50, 50);
  const inline static SDL_Rect S_RECT =
      createRect(SCREEN_WIDTH / 8.0 + 110, SCREEN_HEIGHT / 8.0 + 100, 50, 50);
  const inline static SDL_Rect D_RECT =
      createRect(SCREEN_WIDTH / 8.0 + 165, SCREEN_HEIGHT / 8.0 + 100, 50, 50);
  const inline static SDL_Rect PLAYER_1_MOVE_INSTRUCTION_RECT =
      createRect(SCREEN_WIDTH / 8.0 + 250, SCREEN_HEIGHT / 8.0 + 110, 350, 30);
  inline static SDL_Texture *PLAYER_1_MOVE_INSTRUCTION_TEXTURE =
      loadText(RENDERER, FONT, "Move the blue bats", Instruction::BLUE_COLOR);

  const inline static SDL_Rect F_RECT =
      createRect(SCREEN_WIDTH / 8.0 + 82, SCREEN_HEIGHT / 8.0 + 180, 50, 50);
  const inline static SDL_Rect PLAYER_1_SWITCH_INSTRUCTION_RECT =
      createRect(SCREEN_WIDTH / 8.0 + 250, SCREEN_HEIGHT / 8.0 + 190, 450, 30);
  inline static SDL_Texture *PLAYER_1_SWITCH_INSTRUCTION_TEXTURE =
      loadText(RENDERER, FONT, "Switch the blue bat to control",
               Instruction::BLUE_COLOR);

  const inline static SDL_Rect UP_RECT =
      createRect(SCREEN_WIDTH / 8.0, SCREEN_HEIGHT / 8.0 + 460, 50, 50);
  const inline static SDL_Rect LEFT_RECT =
      createRect(SCREEN_WIDTH / 8.0 + 55, SCREEN_HEIGHT / 8.0 + 460, 50, 50);
  const inline static SDL_Rect DOWN_RECT =
      createRect(SCREEN_WIDTH / 8.0 + 110, SCREEN_HEIGHT / 8.0 + 460, 50, 50);
  const inline static SDL_Rect RIGHT_RECT =
      createRect(SCREEN_WIDTH / 8.0 + 165, SCREEN_HEIGHT / 8.0 + 460, 50, 50);
  const inline static SDL_Rect PLAYER_2_MOVE_INSTRUCTION_RECT =
      createRect(SCREEN_WIDTH / 8.0 + 250, SCREEN_HEIGHT / 8.0 + 470, 350, 30);
  inline static SDL_Texture *PLAYER_2_MOVE_INSTRUCTION_TEXTURE =
      loadText(RENDERER, FONT, "Move the red bats", Instruction::RED_COLOR);

  const inline static SDL_Rect K_RECT =
      createRect(SCREEN_WIDTH / 8.0 + 82, SCREEN_HEIGHT / 8.0 + 540, 50, 50);
  const inline static SDL_Rect PLAYER_2_SWITCH_INSTRUCTION_RECT =
      createRect(SCREEN_WIDTH / 8.0 + 250, SCREEN_HEIGHT / 8.0 + 550, 450, 30);
  inline static SDL_Texture *PLAYER_2_SWITCH_INSTRUCTION_TEXTURE = loadText(
      RENDERER, FONT, "Switch the red bat to control", Instruction::RED_COLOR);

public:
  GameState step(const MouseState &mouseState) const {
    if (MENU_BUTTON.isClicked(mouseState)) {
      return GameState::MAIN_MENU;
    }

    SDL_SetRenderDrawColor(RENDERER, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(RENDERER);

    Instruction::BOARD.draw(RENDERER);
    MENU_BUTTON.draw(RENDERER);

    BLUE_BAT.draw(RENDERER);
    RED_BAT.draw(RENDERER);

    SDL_RenderCopy(RENDERER, Instruction::INSTRUCTION_TEXTURE, NULL,
                   &Instruction::INSTRUCTION_RECT);

    SDL_SetRenderDrawColor(RENDERER, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(RENDERER, &Instruction::BACKGROUND_RECT);
    SDL_SetRenderDrawColor(RENDERER, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect(RENDERER, &Instruction::BACKGROUND_RECT);

    SDL_RenderCopy(RENDERER, W_KEY_TEXTURE, NULL, &Instruction::W_RECT);
    SDL_RenderCopy(RENDERER, A_KEY_TEXTURE, NULL, &Instruction::A_RECT);
    SDL_RenderCopy(RENDERER, S_KEY_TEXTURE, NULL, &Instruction::S_RECT);
    SDL_RenderCopy(RENDERER, D_KEY_TEXTURE, NULL, &Instruction::D_RECT);
    SDL_RenderCopy(RENDERER, Instruction::PLAYER_1_MOVE_INSTRUCTION_TEXTURE,
                   NULL, &Instruction::PLAYER_1_MOVE_INSTRUCTION_RECT);

    SDL_RenderCopy(RENDERER, F_KEY_TEXTURE, NULL, &Instruction::F_RECT);
    SDL_RenderCopy(RENDERER, Instruction::PLAYER_1_SWITCH_INSTRUCTION_TEXTURE,
                   NULL, &Instruction::PLAYER_1_SWITCH_INSTRUCTION_RECT);

    SDL_RenderCopy(RENDERER, UP_KEY_TEXTURE, NULL, &Instruction::UP_RECT);
    SDL_RenderCopy(RENDERER, LEFT_KEY_TEXTURE, NULL, &Instruction::LEFT_RECT);
    SDL_RenderCopy(RENDERER, DOWN_KEY_TEXTURE, NULL, &Instruction::DOWN_RECT);
    SDL_RenderCopy(RENDERER, RIGHT_KEY_TEXTURE, NULL, &Instruction::RIGHT_RECT);
    SDL_RenderCopy(RENDERER, Instruction::PLAYER_2_MOVE_INSTRUCTION_TEXTURE,
                   NULL, &Instruction::PLAYER_2_MOVE_INSTRUCTION_RECT);

    SDL_RenderCopy(RENDERER, K_KEY_TEXTURE, NULL, &Instruction::K_RECT);
    SDL_RenderCopy(RENDERER, Instruction::PLAYER_2_SWITCH_INSTRUCTION_TEXTURE,
                   NULL, &Instruction::PLAYER_2_SWITCH_INSTRUCTION_RECT);

    SDL_RenderPresent(RENDERER);

    return GameState::INSTRUCTION;
  }
};
