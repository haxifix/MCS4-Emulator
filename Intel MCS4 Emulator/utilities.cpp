#include "utilities.h"

namespace MCS4 {
  namespace Utils {
    uint8_t uint4_to_uint8(uint4_t b) {
      return static_cast<uint8_t>(b.to_ulong());
    }

    uint8_t combine_uint4_to_uint8(uint4_t a, uint4_t b) {
      return (uint4_to_uint8(a) << 4) | uint4_to_uint8(b);
    }

    uint16_t uint12_to_uint16(uint12_t b) {
      return static_cast<uint16_t>(b.to_ulong());
    }

    std::string uint8_to_string(uint8_t b) {
      std::string r;
      for (int i = 7; i >= 0; --i) {
        r += (b & (1 << i)) ? "1" : "0";
      }
      return r;
    }
  }
}