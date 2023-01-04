#include "inc.hpp"
#include "iostream"

std::map<uint8_t, Register32> reg_map = {{0x40, EAX}, {0x41, ECX}, {0x42, EDX},
                                         {0x43, EBX}, {0x44, ESP}, {0x45, EBP},
                                         {0x46, ESI}, {0x47, EDI}};

void inc4x(Argument &args) {
  Register32 reg = reg_map[args.opcode];
  args.reg_bank.set32(reg, args.reg_bank.load32(reg) + 1);

  Snapshot snapshot{format_instruction("inc", args.reg_bank.name32(reg)), ""
                                                                          ""};

  args.snapshots.push_back(snapshot);
}
