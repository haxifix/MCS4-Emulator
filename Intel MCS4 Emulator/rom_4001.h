#ifndef ROM_4001_H
#define ROM_4001_H

#include <array>
#include <vector>

namespace MCS4 {
  namespace ROM_4001 {
    static const size_t MAX_WORDS = 256;
    enum class OperationMode { ROM, IO };
    using MemoryBank = std::array<uint8_t, MAX_WORDS>;
    struct Chip {
      Chip(MemoryBank m = { 0 }, OperationMode o = OperationMode::ROM)
        : memory(m), mode(o) {}
      void reset();
      uint8_t read_word(size_t i) const;
      bool write_memory(size_t s, std::vector<uint8_t> m);
      friend std::ostream& operator<<(std::ostream&, const Chip&);
    private:
      OperationMode mode;
      MemoryBank memory;
    };
  }
}

#endif