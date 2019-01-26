#include "rom_4001.h"

namespace MCS4 {
  namespace ROM_4001 {
    void Chip::reset() {
      memory.fill(0);
    }

    uint8_t Chip::read_word(size_t i) const {
      return i < std::size(memory) ? memory[i] : 0;
    }

    bool Chip::write_memory(size_t s, std::vector<uint8_t> m) {
      if (std::size(m) + s >= MAX_WORDS) return false;
      std::copy(std::begin(m), std::end(m), std::begin(memory));
      return true;
    }

    std::ostream& operator<<(std::ostream& os, const Chip& c) {
      for (size_t i = 0; i < 20; ++i) {
        os << std::hex << (uint16_t)c.memory[i] << " ";
      }
      return os;
    }
  }
}