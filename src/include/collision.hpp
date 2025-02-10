#pragma once

#include "board.hpp"
#include "object/bat.hpp"
#include "object/puck.hpp"

void handleCollision(Bat &redBat, Bat &blueBat, Puck &puck, Board &board);
