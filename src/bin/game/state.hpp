#pragma once

enum class GameState {
  NO_MATCH,
  IN_MATCH,
  QUIT,
};

struct Stat {
  unsigned int red;
  unsigned int blue;
};
