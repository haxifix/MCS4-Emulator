#include "instruction.h"
#include "cpu_4004.h"
#include <iostream>

namespace MCS4 {
  namespace CPU_4004 {
    namespace InstructionSet {
      bool NOP(uint8_t& insr, CPU_4004::Chip& c) {
        std::cout << "NOP" << std::endl;
        return true;
      }
      bool INC(uint8_t& insr, CPU_4004::Chip& c) {
        uint8_t r = uint4_to_uint8(c.read_reg(insr & 0xF));
        ++r;
        c.step(1);
        return c.write_reg(insr & 0xF, r & 0xF);
      }
      bool NOT_IMPL(uint8_t& insr, CPU_4004::Chip& c) {
        std::cout << "NOT IMPLEMENTED" << std::endl;
        return true;
      }
    }
  }
}