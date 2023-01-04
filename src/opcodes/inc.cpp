#include "inc.hpp"
#include "iostream"

std::map<uint8_t, Register32> reg_map = {{0x40, EAX}, {0x41, ECX}, {0x42, EDX},
                              {0x43, EBX}, {0x44, ESP}, {0x45, EBP},
                              {0x46, ESI}, {0x47, EDI}};

void inc4x(Argument &args, Scanner &scanner, RegisterBank &register_bank,
           Memory &memory) {
  Register32 reg = reg_map[args.opcode];
  register_bank.set32(reg, register_bank.load32(reg) + 1);
}
