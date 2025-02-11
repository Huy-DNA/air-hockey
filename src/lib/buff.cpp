#include "buff.hpp"
#include <SDL_timer.h>
#include <cstdlib>
#include <ctime>

static unsigned long long ONESHOT = 0;
static unsigned long long USED_ONESHOT = 1;

bool Buff::isOneShot() const {
  return this->endMs == ONESHOT || this->endMs == USED_ONESHOT;
}

bool Buff::isDurational() const {
  return !this->isOneShot();
}

bool Buff::consumeOneShot() {
  const bool used = this->endMs == ONESHOT;
  this->endMs = USED_ONESHOT;
  return used;
}

bool Buff::consumeDurational(unsigned long long curMs) {
  return this->endMs >= curMs;
}

Buff drawBuff() {
  static int _ = (srand(time(0)), 0);
  const int index = rand() % static_cast<int>(BuffType::TOTAL_BUFFS);
  const BuffType type = static_cast<BuffType>(index);
  switch (type) {
    case BuffType::WIND:
      return Buff{type, SDL_GetTicks64() + 5000};
    case BuffType::RANDOMIZATION:
      return Buff{type, ONESHOT};
    default:
      throw "Unreachable";
  }
}
