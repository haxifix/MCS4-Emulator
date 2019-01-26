#include <iostream>
#include "cpu_4004.h"

int main() {
  MCS4::CPU_4004::Chip c;
  std::cout << c << std::endl;
  std::vector<uint8_t> program(17);
  std::fill(std::begin(program), std::end(program), 0b01100000);
  c.mask_rom(0, 0, program);
  while (c.cycle()) {
    std::cout << c << std::endl;
    std::cin.get();
  }
  std::cin.ignore();
  std::cin.get();
  return 0;
}