#include "cpu_4004.h"
#include "instruction.h"
#include <iostream>

namespace MCS4 {
  namespace CPU_4004 {
    uint4_t Chip::read_reg(size_t r) const {
      if (r >= NUM_REGISTERS) return 0;
      return reg[r];
    }

    uint8_t Chip::read_reg_pair(size_t rp, bool P) const {
      if (P) {
        if (rp >= NUM_REGISTERS / 2) return 0;
        rp *= 2;
      }
      else {
        if (rp >= NUM_REGISTERS || rp % 2 != 0) return 0;
      }
      return Utils::combine_uint4_to_uint8(reg[rp], reg[rp + 1]);
    }

    bool Chip::write_reg(size_t r, uint4_t v) {
      if (r >= NUM_REGISTERS) return false;
      reg[r] = v;
      return true;
    }

    bool Chip::write_reg_pair(size_t r, bool P, uint8_t v) {
      if (P) {
        if (r >= NUM_REGISTERS / 2) return false;
        r *= 2;
      }
      else {
        if (r >= NUM_REGISTERS || r % 2 != 0) return false;
      }
      reg[r] = (v & 0xF0) >> 4;
      reg[r + 1] = v & 0xF;
      return true;
    }

    Instruction Chip::decode(uint8_t insr) const {
      std::string insr_str = uint8_to_string(insr);
      auto i = std::find(std::begin(instruction_set), std::end(instruction_set), insr_str);
      if (i == std::end(instruction_set)) return { "", InstructionSet::NOT_IMPL };
      return *i;
    }

    bool Chip::mask_rom(size_t r, size_t s, std::vector<uint8_t> m) {
      if (r >= MAX_EXT_PACKAGES) return false;
      return rom_bank[r].write_memory(s, m);
    }

    void Chip::step(uint16_t n) {
      uint16_t _pc = uint12_to_uint16(pc);
      _pc += n;
      pc = _pc;
    }

    bool Chip::cycle() {
      uint16_t _pc = uint12_to_uint16(pc);
      size_t cdb = _pc / 256;
      uint8_t insr = rom_bank[cdb].read_word(_pc % 256);
      Instruction i = decode(insr);
      return i.impl(insr, *this);
    }

    std::ostream& operator<<(std::ostream& os, const Chip& c) {
      os << "ROM0: " << c.rom_bank[0] << std::endl;
      os << "ACC: " << std::hex << c.acc << std::endl;
      os << "PC: " << std::hex << uint12_to_uint16(c.pc) << std::endl;
      os << "SP: " << std::dec << c.sp << std::endl;
      os << "CY: " << std::dec << c.carry << std::endl;
      for (size_t i = 0; i < 3; ++i) {
        if (i == c.sp) os << "->";
        os << "S" << i << ": " << c.stack[i] << std::endl;
      }
      for (size_t i = 0; i < NUM_REGISTERS; ++i) {
        os << "Reg #" << std::dec << i << " = " << std::hex << c.read_reg(i) << std::endl;
      }
      return os;
    }
  }
}