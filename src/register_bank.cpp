#include "register_bank.hpp"

RegisterBank::RegisterBank() {
  registers[EAX] = Register({"eax", 0xbf8db144});
  registers[ECX] = Register({"ecx", 0x88c5cffb});
  registers[EDX] = Register({"edx", 0x1});
  registers[EBX] = Register({"ebx", 0xae5ff4});
  registers[ESP] = Register({"esp", 0xbf8db0bc});
  registers[EBP] = Register({"ebp", 0xbf8db118});
  registers[ESI] = Register({"esi", 0x9a0ca0});
  registers[EDI] = Register({"edi", 0x0});
}

uint32_t RegisterBank::load(const uint32_t &index) {
  return registers[index].value;
}
