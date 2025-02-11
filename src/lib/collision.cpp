#include "board.hpp"
#include "object/bat.hpp"
#include "object/puck.hpp"
#include "vector2d.hpp"
#include <cstdio>

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

  bat1.setPosition(bat1.getPosition() - distVec.normalize() * diff / 10);
  bat2.setPosition(bat2.getPosition() + distVec.normalize() * diff);
}

void reflectOffBat(Puck &puck, Bat &bat) {
  if (!bat.doesCollide(puck)) {
    return;
  }
  Vector2d collisionPoint = bat.getCollisionPoint(puck);
  Vector2d norm = (collisionPoint - bat.getPosition()).normalize();
  Vector2d reflectedVelocity =
      (puck.getVelocity() - bat.getVelocity()).reflect(norm) +
      bat.getVelocity();
  puck.setVelocity(reflectedVelocity);
}

void reflectOffBoard(Puck &puck, Board &board) {
  const Vector2d velocity = puck.getVelocity();
  if (puck.doesCollideLeft(board)) {
    Vector2d norm = Vector2d{1, 0};
    puck.setVelocity(velocity.reflect(norm));
  }
  if (puck.doesCollideRight(board)) {
    Vector2d norm = Vector2d{-1, 0};
    puck.setVelocity(velocity.reflect(norm));
  }
  if (puck.doesCollideUp(board)) {
    Vector2d norm = Vector2d{0, 1};
    puck.setVelocity(velocity.reflect(norm));
  }
  if (puck.doesCollideDown(board)) {
    Vector2d norm = Vector2d{0, -1};
    puck.setVelocity(velocity.reflect(norm));
  }
}
