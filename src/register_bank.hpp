#ifndef REGISTER_BANK_H
#define REGISTER_BANK_H

#include <string>

enum Register8 { AH, AL, CH, CL, DH, DL, BH, BL };

enum Register16 { AX, CX, DX, BX, SP, BP, SI, DI };

enum Register32 { EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI };

enum Register64 {
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
  uint64_t value;
  std::string name8;
  std::string name16;
  std::string name32;
  std::string name64;
};

class RegisterBank {
private:
  Register m_registers[8];

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
  std::string name8(const uint32_t &index);
  std::string name16(const uint32_t &index);
  std::string name32(const uint32_t &index);
  std::string name64(const uint32_t &index);
};

#endif
