#pragma once

enum class BuffType {
  WIND,
  RANDOMIZATION,
  TOTAL_BUFFS,
};

BuffType drawBuff();

struct Buff {
  BuffType type;
  unsigned long long endMs;
};
