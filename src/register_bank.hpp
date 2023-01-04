#ifndef REGISTER_BANK_H
#define REGISTER_BANK_H

#include <string>

enum x86_8bit_registers { AL, CL, DL, BL, AH, CH, DH, BH };

enum x86_16bit_registers { AX, CX, DX, BX, SP, BP, SI, DI };

enum x86_32bit_registers { EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI };

enum x86_64bit_registers {
  RAX,
  RCX,
  RDX,
  RBX,
  RSP,
  RBP,
  RSI,
  RDI,
  R8,
  R9,
  R10,
  R11,
  R12,
  R13,
  R14,
  R15
};

struct Register {
  std::string name;
  uint64_t value;
};

class RegisterBank {
private:
  Register registers[8];

public:
  RegisterBank();
  uint8_t load8(const uint32_t &index);
  uint16_t load16(const uint32_t &index);
  uint32_t load32(const uint32_t &index);
  uint64_t load64(const uint32_t &index);
  void set8(const uint32_t &index, const uint8_t value);
  void set16(const uint32_t &index, const uint16_t value);
  void set32(const uint32_t &index, const uint32_t value);
  void set64(const uint32_t &index, const uint64_t value);
};

#endif
