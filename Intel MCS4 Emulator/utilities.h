#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <bitset>
#include <vector>
#include <string>

namespace MCS4 {
  namespace Utils {
    using uint4_t = std::bitset<4>;
    using uint12_t = std::bitset<12>;
    uint8_t uint4_to_uint8(uint4_t b);
    uint8_t combine_uint4_to_uint8(uint4_t a, uint4_t b);
    uint16_t uint12_to_uint16(uint12_t b);
    std::string uint8_to_string(uint8_t b);
  }
}

#endif