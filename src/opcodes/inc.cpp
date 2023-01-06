#include "inc.hpp"
#include <iostream>

std::map<uint8_t, Register32> reg_map = {{0x40, EAX}, {0x41, ECX}, {0x42, EDX},
                                         {0x43, EBX}, {0x44, ESP}, {0x45, EBP},
                                         {0x46, ESI}, {0x47, EDI}};

void inc4x(State &state) {
  Register32 reg = reg_map[state.args.opcode];
  uint32_t reg_value = state.reg_bank.load32(reg);
  std::string reg_name = state.reg_bank.name32(reg);

  state.reg_bank.set32(reg, reg_value + 1);

  set_snapshot(state, "inc", reg_value, state.reg_bank.load32(reg),
               state.reg_bank.name32(reg));
}
