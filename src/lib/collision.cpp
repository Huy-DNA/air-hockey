#include "board.hpp"
#include "object/bat.hpp"
#include "object/puck.hpp"

void handleRedBatCollision(Bat &bat, Puck &puck, Board &board) {
  if (bat.doesCollide(puck)) {
    puck.addVelocity(bat.getVelocity());
  }


  for (int i = 0; i < 100 && bat.doesCollide(puck); ++i) {
    const Vector2d distVec = puck.getPosition() - bat.getPosition();

    const float dist = distVec.length();
    const float sumRadius = bat.getSize() + puck.getSize();
    const float diff = sumRadius - dist;

    bat.setPosition(bat.getPosition() - distVec.normalize() * diff / 20);
    puck.setPosition(puck.getPosition() + distVec.normalize() * diff * 1.3);

    board.capPuckPosition(puck);
    board.capRedBatPosition(bat);
  }
}

void handleBlueBatCollision(Bat &bat, Puck &puck, Board &board) {
  if (bat.doesCollide(puck)) {
    puck.addVelocity(bat.getVelocity());
  }

  for (int i = 0; i < 100 && bat.doesCollide(puck); ++i) {
    const Vector2d distVec = puck.getPosition() - bat.getPosition();

    const float dist = distVec.length();
    const float sumRadius = bat.getSize() + puck.getSize();
    const float diff = sumRadius - dist;

    bat.setPosition(bat.getPosition() - distVec.normalize() * diff / 20);
    puck.setPosition(puck.getPosition() + distVec.normalize() * diff * 1.3);

    board.capPuckPosition(puck);
    board.capBlueBatPosition(bat);
  }
}
