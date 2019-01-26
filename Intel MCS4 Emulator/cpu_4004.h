#ifndef CPU_4004_H
#define CPU_4004_H

#include <array>
#include <vector>

#include "utilities.h"
#include "rom_4001.h"
#include "instruction.h"

using namespace MCS4::Utils;

namespace MCS4 {
  namespace CPU_4004 {
    static const size_t NUM_REGISTERS = 16;
    static const size_t MAX_EXT_PACKAGES = 48;
    struct Chip {
      void step(uint16_t n);
      bool cycle();
      bool mask_rom(size_t r, size_t s, std::vector<uint8_t> m);
      uint4_t read_reg(size_t r) const;
      uint8_t read_reg_pair(size_t rp, bool P) const;
      bool write_reg(size_t r, uint4_t v);
      bool write_reg_pair(size_t r, bool P, uint8_t v);
      friend std::ostream& operator<<(std::ostream&, const Chip&);
    private:
      std::array<ROM_4001::Chip, MAX_EXT_PACKAGES> rom_bank;
      std::array<uint4_t, NUM_REGISTERS> reg = { 0 };
      uint4_t acc = 0;
      uint12_t pc = 0;
      uint12_t stack[3] = { 0 };
      size_t sp = 0;
      bool carry = false;
      Instruction decode(uint8_t insr) const;
      std::vector<Instruction> instruction_set = {
        { "00000000", InstructionSet::NOP },
        { "0110????", InstructionSet::INC },
      };
    };
  }
}

#endif