#include <unordered_set>

class KeyState {
private:
  std::unordered_set<unsigned int> triggeredKeys;

public:
  KeyState() {};
  void set(unsigned int key) { this->triggeredKeys.insert(key); }
  void reset(unsigned int key) { this->triggeredKeys.erase(key); }
  template <class... Types> bool isTriggered(unsigned int key, Types... keys) {
    if (!this->triggeredKeys.count(key)) {
      return false;
    }
    return this->triggeredKeys(keys...);
  }
  bool isTriggered(unsigned int key) {
    return !!this->triggeredKeys.count(key);
  }
};
