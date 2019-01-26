#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <functional>

#include "utilities.h"

using namespace MCS4::Utils;

namespace MCS4 {
  namespace CPU_4004 {
    struct Chip;
    struct Instruction {
      bool operator==(const std::string& s) const {
        for (size_t i = 0; i < s.length(); ++i) {
          if (form[i] != '?') {
            if (s[i] != form[i]) return false;
          }
        }
        return true;
      }

      std::string form;
      std::function<bool(uint8_t&, CPU_4004::Chip&)> impl;
    };
    namespace InstructionSet {
      bool NOP(uint8_t&, CPU_4004::Chip&);
      bool INC(uint8_t&, CPU_4004::Chip&);
      bool NOT_IMPL(uint8_t&, CPU_4004::Chip&);
    }
  }
}

#endif