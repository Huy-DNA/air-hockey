#pragma once

#include "board.hpp"
#include "object/bat.hpp"
#include "object/puck.hpp"

void reflectOffBat(Puck &puck, Bat &bat);

// Adjust bats and puck positions slightly such that they do not collide
void uncollide(Bat &redBat, Bat &blueBat, Puck &puck, Board &board);
