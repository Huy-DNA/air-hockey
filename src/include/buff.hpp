#pragma once

enum class BuffType {
  NONE,
  WIND,
  RANDOMIZATION,
  TOTAL_BUFFS,
};

BuffType drawBuff();
