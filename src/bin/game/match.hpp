#pragma once

#include "board.hpp"
#include "button.hpp"
#include "collision.hpp"
#include "constants.hpp"
#include "keystate.hpp"
#include "mousestate.hpp"
#include "object/bat.hpp"
#include "object/puck.hpp"
#include "piece.hpp"
#include "sdl_utils.hpp"
#include "state.hpp"
#include "windbar.hpp"
#include <SDL_keycode.h>
#include <SDL_mixer.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <array>
#include <cstdlib>

struct Stat {
  unsigned int red;
  unsigned int blue;
};

class Match {
private:
  const inline static Button MENU_BUTTON = Button(
      createColor(0x00, 0x00, 0x00, 0xFF), createColor(0x00, 0xFF, 0xFF, 0xFF),
      FONT, createRect(SCREEN_WIDTH / 2 + 200, 25, 100, 50), "MENU");

  Stat stat{0, 0};

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

  WindBar windBar = WindBar(WIND_LEFT_TEXTURE, WIND_RIGHT_TEXTURE, FONT,
                            {SCREEN_WIDTH / 2.0, 50});
  unsigned long long windMs = SDL_GetTicks64();

  const SDL_Rect blueScoreRect = createRect(board.getLeft() + 70, 25, 75, 75);
  const SDL_Rect redScoreRect = createRect(board.getRight() - 200, 25, 75, 75);

  unsigned long long prevMs = SDL_GetTicks64();

public:
  void hardReset() {
    this->softReset();
    this->stat = {0, 0};
  }

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

    this->puck = Puck(PUCK_SPRITE, board.getInitPuckPos(), PUCK_SIZE / 2.0);

    this->windBar = WindBar(WIND_LEFT_TEXTURE, WIND_RIGHT_TEXTURE, FONT,
                            {SCREEN_WIDTH / 2.0, 50});
    this->windMs = SDL_GetTicks64();

    this->prevMs = SDL_GetTicks64();
  }

  GameState step(const KeyState &keyState, const MouseState &mouseState) {
    unsigned long long curMs = SDL_GetTicks64();
    unsigned long long deltaMs = curMs - this->prevMs;

    // Update states
    if (MENU_BUTTON.isClicked(mouseState)) {
      return GameState::MAIN_MENU;
    }

    /// Update wind
    if (curMs - windMs > 5000) {
      windMs = curMs;
      if (windBar.getWindRate() != 0) {
        windBar.setWindRate(0);
      } else {
        windBar.setWindRate((rand() * 1.0 / RAND_MAX - 0.5) * 2);
      }
    }
    puck.addVelocity(windBar.getWindVelocity() * deltaMs / 1000);
    /// Switch pieces
    static bool prevFPressed = false;
    static bool prevKPressed = false;
    const bool FPressed = keyState.isTriggered(SDLK_f);
    const bool KPressed = keyState.isTriggered(SDLK_k);
    if (!prevFPressed && FPressed) {
      curBlueBat = curBlueBat == &blueBatOne ? &blueBatTwo : &blueBatOne;
    }
    if (!prevKPressed && KPressed) {
      curRedBat = curRedBat == &redBatOne ? &redBatTwo : &redBatOne;
    }
    prevFPressed = FPressed;
    prevKPressed = KPressed;
    /// Set velocity of bats
    blueBatOne.setVelocity({0.0, 0.0});
    blueBatTwo.setVelocity({0.0, 0.0});
    if (keyState.isTriggered(SDLK_a)) {
      curBlueBat->addVelocity({-1.0, 0.0});
    }
    if (keyState.isTriggered(SDLK_d)) {
      curBlueBat->addVelocity({1.0, 0.0});
    }
    if (keyState.isTriggered(SDLK_w)) {
      curBlueBat->addVelocity({0.0, -1.0});
    }
    if (keyState.isTriggered(SDLK_s)) {
      curBlueBat->addVelocity({0.0, 1.0});
    }

    redBatOne.setVelocity({0.0, 0.0});
    redBatTwo.setVelocity({0.0, 0.0});
    if (keyState.isTriggered(SDLK_LEFT)) {
      curRedBat->addVelocity({-1.0, 0.0});
    }
    if (keyState.isTriggered(SDLK_RIGHT)) {
      curRedBat->addVelocity({1.0, 0.0});
    }
    if (keyState.isTriggered(SDLK_UP)) {
      curRedBat->addVelocity({0.0, -1.0});
    }
    if (keyState.isTriggered(SDLK_DOWN)) {
      curRedBat->addVelocity({0.0, 1.0});
    }

    bool soundPlayed = false;
    // Split the movement & collision over the time period (50 rounds)
    // To prevent the phenomenon that deltaMs is too large, making the puck
    // penetrate through a colliding bat as the jump is too large
    for (int i = 0; i < 50; ++i) {
      /// Set position
      curBlueBat->move(deltaMs / 50.0);
      curRedBat->move(deltaMs / 50.0);
      puck.move(deltaMs / 50.0);

      /// Play sound on collision
      if ((puck.doesCollide(redBatOne) || puck.doesCollide(redBatTwo) ||
           puck.doesCollide(blueBatOne) || puck.doesCollide(blueBatTwo) ||
           puck.doesCollideDown(board) || puck.doesCollideLeft(board) ||
           puck.doesCollideRight(board) || puck.doesCollideUp(board)) &&
          !soundPlayed) {
        soundPlayed = true;
        Mix_HaltChannel(1);
        Mix_PlayChannel(1, SMACK_SOUND, 1);
      }

      if (board.doesPuckCollideWithGoal(Color::BLUE, puck)) {
        this->stat.blue += 1;
        return GameState::CONTINUE_MATCH;
      }

      if (board.doesPuckCollideWithGoal(Color::RED, puck)) {
        this->stat.red += 1;
        return GameState::CONTINUE_MATCH;
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
    windBar.draw(RENDERER);
    MENU_BUTTON.draw(RENDERER);
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

    return GameState::IN_MATCH;
  }
};
