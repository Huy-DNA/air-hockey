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

void uncollide(Bat &redBat, Bat &blueBat, Puck &puck, Board &board) {
  for (int i = 0;
       i < 100 && (redBat.doesCollide(puck) || blueBat.doesCollide(puck));
       ++i) {

    uncollideBatAndPuck(redBat, puck);
    uncollideBatAndPuck(blueBat, puck);

    board.capPuckPosition(puck);
    board.capRedBatPosition(redBat);
    board.capBlueBatPosition(blueBat);
  }
  board.capPuckPosition(puck);
  board.capRedBatPosition(redBat);
  board.capBlueBatPosition(blueBat);
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
