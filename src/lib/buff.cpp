#include "buff.hpp"
#include <cstdlib>
#include <ctime>

static int _ = (srand(time(0)), 0);

BuffType drawBuff() { 
  const int index = rand() % static_cast<int>(BuffType::TOTAL_BUFFS);
  return static_cast<BuffType>(index);
}
