#pragma once

enum class GameState {
  MAIN_MENU,
  START_MATCH,
  IN_MATCH,
  QUIT,
};

struct Stat {
  unsigned int red;
  unsigned int blue;
};
