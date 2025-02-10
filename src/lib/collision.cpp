#include "board.hpp"
#include "object/bat.hpp"
#include "object/puck.hpp"

static void adjustBatAndPuck(Bat &bat, Puck &puck) {
  if (!bat.doesCollide(puck)) {
    return;
  }

  const Vector2d distVec = puck.getPosition() - bat.getPosition();

  const float dist = distVec.length();
  const float sumRadius = bat.getSize() + puck.getSize();
  const float diff = sumRadius - dist;

  bat.setPosition(bat.getPosition() - distVec.normalize() * diff / 30);
  puck.setPosition(puck.getPosition() + distVec.normalize() * diff);
}

void handleCollision(Bat &redBat, Bat &blueBat, Puck &puck, Board &board) {
  if (redBat.doesCollide(puck)) {
    puck.addVelocity(redBat.getVelocity());
  }
  if (blueBat.doesCollide(puck)) {
    puck.addVelocity(blueBat.getVelocity());
  }
  for (int i = 0;
       i < 100 && (redBat.doesCollide(puck) || blueBat.doesCollide(puck));
       ++i) {

    adjustBatAndPuck(redBat, puck);
    adjustBatAndPuck(blueBat, puck);

    board.capPuckPosition(puck);
    board.capRedBatPosition(redBat);
    board.capBlueBatPosition(blueBat);
  }
}
