#include "buff.hpp"
#include <cstdlib>
#include <ctime>

static int _ = (srand(time(0)), 0);

Buff drawBuff() { 
  const int index = rand() % static_cast<int>(Buff::TOTAL_BUFFS);
  return static_cast<Buff>(index);
}
