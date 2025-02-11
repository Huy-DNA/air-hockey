#pragma once

#include "board.hpp"
#include "object/bat.hpp"
#include "object/puck.hpp"
#include <array>

void reflectOffBat(Puck &puck, Bat &bat);
void reflectOffBoard(Puck &puck, Board &board);

// Adjust bats and puck positions slightly such that they do not collide
static void uncollideBatAndPuck(Bat &bat, Puck &puck);
static void uncollideBatAndBat(Bat &bat1, Bat &bat2);
template <std::size_t n>
void uncollide(std::array<Bat *, n> bats, Puck &puck, Board &board) {
  for (int i = 0; i < 100; ++i) {
    bool doesCollide = false;
    for (const Bat *bat : bats) {
      doesCollide = doesCollide || bat->doesCollide(puck);
    }
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        doesCollide = doesCollide || bats[i]->doesCollide(*bats[j]);
      }
    }
    if (!doesCollide)
      break;

    for (Bat *bat : bats) {
      uncollideBatAndPuck(*bat, puck);
    }
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        uncollideBatAndBat(*bats[i], *bats[j]);
      }
    }

    board.capPuckPosition(puck);
    for (Bat *bat : bats) {
      board.capBatPosition(*bat);
    }
  }
  board.capPuckPosition(puck);
  for (Bat *bat : bats) {
    board.capBatPosition(*bat);
  }
}

static void uncollideBatAndPuck(Bat &bat, Puck &puck) {
  if (!bat.doesCollide(puck)) {
    return;
  }

  const Vector2d distVec = puck.getPosition() - bat.getPosition();

  const float dist = distVec.length();
  const float sumRadius = bat.getSize() + puck.getSize();
  const float diff = sumRadius - dist;

  bat.setPosition(bat.getPosition() - distVec.normalize() * diff / 10);
  puck.setPosition(puck.getPosition() + distVec.normalize() * diff);
}

static void uncollideBatAndBat(Bat &bat1, Bat &bat2) {
  if (!bat1.doesCollide(bat2)) {
    return;
  }

  const Vector2d distVec = bat2.getPosition() - bat1.getPosition();

  const float dist = distVec.length();
  const float sumRadius = bat1.getSize() + bat2.getSize();
  const float diff = sumRadius - dist;

  const bool isBat1Moving = bat1.getVelocity().length() > 0;
  bat1.setPosition(bat1.getPosition() - distVec.normalize() * (diff * isBat1Moving));
  bat2.setPosition(bat2.getPosition() + distVec.normalize() * (diff * !isBat1Moving));
}
