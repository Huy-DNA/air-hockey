#pragma once

#include "board.hpp"
#include "buff.hpp"
#include "collision.hpp"
#include "constants.hpp"
#include "animation/energy_bar.hpp"
#include "keystate.hpp"
#include "object/bat.hpp"
#include "object/puck.hpp"
#include "piece.hpp"
#include "sdl_utils.hpp"
#include "state.hpp"
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <array>

class Match {
public:
  enum class Winner {
    NONE,
    RED,
    BLUE,
  };

private:
  Board board = Board(FIELD_TEXTURE, 0, 100, FIELD_WIDTH, FIELD_HEIGHT);

  Bat blueBatOne =
      Bat(BAT_BLUE_SPRITE, Color::BLUE,
          board.getInitBatPos(Color::BLUE, Ally::ONE), BAT_SIZE / 2.0);
  Bat blueBatTwo =
      Bat(BAT_BLUE_SPRITE, Color::BLUE,
          board.getInitBatPos(Color::BLUE, Ally::TWO), BAT_SIZE / 2.0);
  Bat *curBlueBat = &blueBatOne;

  Bat redBatOne =
      Bat(BAT_RED_SPRITE, Color::RED,
          board.getInitBatPos(Color::RED, Ally::ONE), BAT_SIZE / 2.0);
  Bat redBatTwo =
      Bat(BAT_RED_SPRITE, Color::RED,
          board.getInitBatPos(Color::RED, Ally::TWO), BAT_SIZE / 2.0);
  Bat *curRedBat = &redBatOne;

  Puck puck = Puck(PUCK_SPRITE, board.getInitPuckPos(), PUCK_SIZE / 2.0);

  EnergyBar blueBar = EnergyBar(
      createRect(10, SCREEN_HEIGHT - FIELD_HEIGHT - 75, SCREEN_WIDTH / 3, 50),
      createColor(0x00, 0x00, 0xFF, 0xFF),
      0.001);
  EnergyBar redBar = EnergyBar(
      createRect(920, SCREEN_HEIGHT - FIELD_HEIGHT - 75, SCREEN_WIDTH / 3, 50),
      createColor(0xFF, 0x00, 0x00, 0xFF),
      0.001);

  Buff blueBuff = Buff{};
  Buff redBuff = Buff{};

  const SDL_Rect blueScoreRect = createRect(550, 25, 75, 75);
  const SDL_Rect redScoreRect = createRect(750, 25, 75, 75);

  unsigned long long prevMs = SDL_GetTicks64();

public:
  void softReset() {
    this->blueBatOne =
        Bat(BAT_BLUE_SPRITE, Color::BLUE,
            board.getInitBatPos(Color::BLUE, Ally::ONE), BAT_SIZE / 2.0);
    this->blueBatTwo =
        Bat(BAT_BLUE_SPRITE, Color::BLUE,
            board.getInitBatPos(Color::BLUE, Ally::TWO), BAT_SIZE / 2.0);
    this->curBlueBat = &blueBatOne;

    this->redBatOne =
        Bat(BAT_RED_SPRITE, Color::RED,
            board.getInitBatPos(Color::RED, Ally::ONE), BAT_SIZE / 2.0);
    this->redBatTwo =
        Bat(BAT_RED_SPRITE, Color::RED,
            board.getInitBatPos(Color::RED, Ally::TWO), BAT_SIZE / 2.0);
    this->curRedBat = &redBatOne;

    this->blueBuff = Buff{};
    this->redBuff = Buff{};

    this->puck = Puck(PUCK_SPRITE, board.getInitPuckPos(), PUCK_SIZE / 2.0);

    this->prevMs = SDL_GetTicks64();
  }

  Winner step(Stat stat, const KeyState &keyStates) {
    unsigned long long curMs = SDL_GetTicks64();
    unsigned long long deltaMs = curMs - this->prevMs;

    // Update states
    /// Switch pieces
    static bool prevFPressed = false;
    static bool prevKPressed = false;
    const bool FPressed = keyStates.isTriggered(SDLK_f);
    const bool KPressed = keyStates.isTriggered(SDLK_k);
    if (!prevFPressed && FPressed) {
      curBlueBat = curBlueBat == &blueBatOne ? &blueBatTwo : &blueBatOne;
    }
    if (!prevKPressed && KPressed) {
      curRedBat = curRedBat == &redBatOne ? &redBatTwo : &redBatOne;
    }
    prevFPressed = FPressed;
    prevKPressed = KPressed;
    /// Activate buffs
    if (blueBar.isFull() && keyStates.isTriggered(SDLK_g)) {
      blueBuff = drawBuff();
      blueBar.setPercent(0);
    }
    if (redBar.isFull() && keyStates.isTriggered(SDLK_l)) {
      redBuff = drawBuff();
      redBar.setPercent(0);
    }
    /// Handle buffs
    if (blueBuff.type == BuffType::WIND && blueBuff.consumeDurational(curMs)) {
      puck.addVelocity({0.001f * deltaMs, 0});
    } else if (blueBuff.type == BuffType::RANDOMIZATION &&
               blueBuff.consumeOneShot()) {
      redBatOne.setPosition(board.getRandomBatPos(Color::RED));
      redBatTwo.setPosition(board.getRandomBatPos(Color::RED));
    }
    if (redBuff.type == BuffType::WIND && redBuff.consumeDurational(curMs)) {
      puck.addVelocity({-0.001f * deltaMs, 0});
    } else if (redBuff.type == BuffType::RANDOMIZATION &&
               redBuff.consumeOneShot()) {
      blueBatOne.setPosition(board.getRandomBatPos(Color::BLUE));
      blueBatTwo.setPosition(board.getRandomBatPos(Color::BLUE));
    }

    /// Set velocity of bats
    blueBatOne.setVelocity({0.0, 0.0});
    blueBatTwo.setVelocity({0.0, 0.0});
    if (keyStates.isTriggered(SDLK_a)) {
      curBlueBat->addVelocity({-1.0, 0.0});
    }
    if (keyStates.isTriggered(SDLK_d)) {
      curBlueBat->addVelocity({1.0, 0.0});
    }
    if (keyStates.isTriggered(SDLK_w)) {
      curBlueBat->addVelocity({0.0, -1.0});
    }
    if (keyStates.isTriggered(SDLK_s)) {
      curBlueBat->addVelocity({0.0, 1.0});
    }

    redBatOne.setVelocity({0.0, 0.0});
    redBatTwo.setVelocity({0.0, 0.0});
    if (keyStates.isTriggered(SDLK_LEFT)) {
      curRedBat->addVelocity({-1.0, 0.0});
    }
    if (keyStates.isTriggered(SDLK_RIGHT)) {
      curRedBat->addVelocity({1.0, 0.0});
    }
    if (keyStates.isTriggered(SDLK_UP)) {
      curRedBat->addVelocity({0.0, -1.0});
    }
    if (keyStates.isTriggered(SDLK_DOWN)) {
      curRedBat->addVelocity({0.0, 1.0});
    }

    // Split the movement & collision over the time period (50 rounds)
    // To prevent the phenomenon that deltaMs is too large, making the puck
    // penetrate through a colliding bat as the jump is too large
    for (int i = 0; i < 50; ++i) {
      /// Set position
      curBlueBat->move(deltaMs / 50.0);
      curRedBat->move(deltaMs / 50.0);

      if (puck.doesCollide(*curBlueBat)) {
        blueBar.addPercent(0.05);
      }

      if (puck.doesCollide(*curRedBat)) {
        redBar.addPercent(0.05);
      }

      puck.move(deltaMs / 50.0);

      if (board.doesPuckCollideWithGoal(Color::BLUE, puck)) {
        return Winner::RED;
      }

      if (board.doesPuckCollideWithGoal(Color::RED, puck)) {
        return Winner::BLUE;
      }

      /// Reflect
      reflectOffBat(puck, redBatOne);
      reflectOffBat(puck, redBatTwo);
      reflectOffBat(puck, blueBatOne);
      reflectOffBat(puck, blueBatTwo);
      reflectOffBoard(puck, board);

      /// Adjust all the pieces' positions slightly to a consistent state
      uncollide(std::array<Bat *, 4>{&redBatOne, &redBatTwo, &blueBatOne,
                                     &blueBatTwo},
                puck, board);
    }

    // Render image
    SDL_SetRenderDrawColor(RENDERER, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(RENDERER);
    board.draw(RENDERER);
    blueBatOne.draw(RENDERER);
    blueBatTwo.draw(RENDERER);
    redBatOne.draw(RENDERER);
    redBatTwo.draw(RENDERER);
    puck.draw(RENDERER);
    redBar.draw(RENDERER, deltaMs);
    blueBar.draw(RENDERER, deltaMs);
    SDL_RenderCopy(RENDERER,
                   loadText(RENDERER, FONT, std::to_string(stat.blue),
                            createColor(0x00, 0x00, 0xFF, 0xFF)),
                   NULL, &blueScoreRect);
    SDL_RenderCopy(RENDERER,
                   loadText(RENDERER, FONT, std::to_string(stat.red),
                            createColor(0xFF, 0x00, 0x00, 0xFF)),
                   NULL, &redScoreRect);
    SDL_RenderPresent(RENDERER);

    // Epilog
    while (SDL_GetTicks64() - curMs < 1000 / 60)
      ;
    this->prevMs = curMs;

    return Winner::NONE;
  }
};
