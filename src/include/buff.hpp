#pragma once

enum class BuffType {
  WIND,
  RANDOMIZATION,
  TOTAL_BUFFS,
};

struct Buff {
  BuffType type;
  unsigned long long endMs;
  
  bool isOneShot() const;
  bool isDurational() const;
  bool consumeOneShot();
  bool consumeDurational(unsigned long long curMs);
};

Buff drawBuff();
