#pragma once

#include "board.hpp"
#include "object/bat.hpp"
#include "object/puck.hpp"

void handleRedBatCollision(Bat &bat, Puck &puck, Board &board);
void handleBlueBatCollision(Bat &bat, Puck &puck, Board &board);
