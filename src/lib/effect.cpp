#include "effect.hpp"
#include <cstdlib>
#include <ctime>

static int _ = (srand(time(0)), 0);

Effect drawEffect() { 
  const int index = rand() % static_cast<int>(Effect::TOTAL_EFFECTS);
  return static_cast<Effect>(index);
}
