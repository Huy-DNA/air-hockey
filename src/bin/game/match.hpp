#pragma once

#include "energy_bar.hpp"
#include "sdl_utils.hpp"
#include "state.hpp"
#include "board.hpp"
#include "collision.hpp"
#include "constants.hpp"
#include "keystate.hpp"
#include "object/bat.hpp"
#include "object/puck.hpp"
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <SDL_timer.h>

class Match {
public:
  enum class Winner {
    NONE,
    RED,
    BLUE,
  };

private:
  Board board = Board(FIELD_TEXTURE, 0, 100, FIELD_WIDTH, FIELD_HEIGHT);
  Bat blueBat = Bat(BAT_BLUE_SPRITE, board.getInitBlueBatPos(), BAT_SIZE / 2.0);
  Bat redBat = Bat(BAT_RED_SPRITE, board.getInitRedBatPos(), BAT_SIZE / 2.0);
  Puck puck = Puck(PUCK_SPRITE, board.getInitPuckPos(), PUCK_SIZE / 2.0);
  EnergyBar blueBar = EnergyBar(createRect(10, SCREEN_HEIGHT - FIELD_HEIGHT - 75, SCREEN_WIDTH / 3, 50), createColor(0x00, 0x00, 0xFF, 0xFF));
  EnergyBar redBar = EnergyBar(createRect(920, SCREEN_HEIGHT - FIELD_HEIGHT - 75, SCREEN_WIDTH / 3, 50), createColor(0xFF, 0x00, 0x00, 0xFF));
  unsigned long long prevMs = SDL_GetTicks64();
  const SDL_Rect blueScoreRect = createRect(550, 25, 75, 75);
  const SDL_Rect redScoreRect = createRect(750, 25, 75, 75);

public:
  void softReset() {
    this->blueBat =
        Bat(BAT_BLUE_SPRITE, board.getInitBlueBatPos(), BAT_SIZE / 2.0);
    this->redBat =
        Bat(BAT_RED_SPRITE, board.getInitRedBatPos(), BAT_SIZE / 2.0);
    this->puck = Puck(PUCK_SPRITE, board.getInitPuckPos(), PUCK_SIZE / 2.0);
    this->prevMs = SDL_GetTicks64();
  }

  Winner step(Stat stat, const KeyState &keyStates) {
    unsigned long long curMs = SDL_GetTicks64();
    unsigned long long deltaMs = curMs - this->prevMs;

    // Update states
    /// Set velocity of bats
    blueBat.setVelocity({0.0, 0.0});
    if (keyStates.isTriggered(SDLK_a)) {
      blueBat.addVelocity({-1.0, 0.0});
    }
    if (keyStates.isTriggered(SDLK_d)) {
      blueBat.addVelocity({1.0, 0.0});
    }
    if (keyStates.isTriggered(SDLK_w)) {
      blueBat.addVelocity({0.0, -1.0});
    }
    if (keyStates.isTriggered(SDLK_s)) {
      blueBat.addVelocity({0.0, 1.0});
    }

    redBat.setVelocity({0.0, 0.0});
    if (keyStates.isTriggered(SDLK_LEFT)) {
      redBat.addVelocity({-1.0, 0.0});
    }
    if (keyStates.isTriggered(SDLK_RIGHT)) {
      redBat.addVelocity({1.0, 0.0});
    }
    if (keyStates.isTriggered(SDLK_UP)) {
      redBat.addVelocity({0.0, -1.0});
    }
    if (keyStates.isTriggered(SDLK_DOWN)) {
      redBat.addVelocity({0.0, 1.0});
    }

    // Split the movement & collision over the time period (50 rounds)
    // To prevent the phenomenon that deltaMs is too large, making the puck
    // penetrate through a colliding bat as the jump is too large
    for (int i = 0; i < 50; ++i) {
      /// Set position
      blueBat.move(deltaMs / 50.0);
      redBat.move(deltaMs / 50.0);
      puck.move(deltaMs / 50.0);

      if (puck.doesCollide(blueBat)) {
        blueBar.addPercent(0.1);
      }

      if (puck.doesCollide(redBat)) {
        redBar.addPercent(0.1);
      }

      if (board.doesPuckCollideWithBlueGoal(puck)) {
        return Winner::RED;
      }

      if (board.doesPuckCollideWithRedGoal(puck)) {
        return Winner::BLUE;
      }

      /// Reflect
      reflectOffBat(puck, redBat);
      reflectOffBat(puck, blueBat);
      reflectOffBoard(puck, board);

      /// Adjust all the pieces' positions slightly to a consistent state
      uncollide(redBat, blueBat, puck, board);
    }

    // Render image
    SDL_SetRenderDrawColor(RENDERER, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(RENDERER);
    board.draw(RENDERER);
    blueBat.draw(RENDERER);
    redBat.draw(RENDERER);
    puck.draw(RENDERER);
    redBar.draw(RENDERER);
    blueBar.draw(RENDERER);
    SDL_RenderCopy(RENDERER, loadText(RENDERER, FONT, std::to_string(stat.blue), createColor(0x00, 0x00, 0xFF, 0xFF)), NULL, &blueScoreRect);
    SDL_RenderCopy(RENDERER, loadText(RENDERER, FONT, std::to_string(stat.red), createColor(0xFF, 0x00, 0x00, 0xFF)), NULL, &redScoreRect);
    SDL_RenderPresent(RENDERER);

    // Epilog
    while (SDL_GetTicks64() - curMs < 1000 / 60)
      ;
    this->prevMs = curMs;

    return Winner::NONE;
  }
};
