#ifndef REGISTER_BANK_H
#define REGISTER_BANK_H

#include <string>

enum OperandSize { OPERAND_8, OPERAND_16, OPERAND_32, OPERAND_64 };

enum Register8 { AL, CL, DL, BL, AH, CH, DH, BH };

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

enum RegisterSeg { CS, DS, SS, ES, FS, GS };

enum FLAG {
  CF,
  PF = 2,
  AF = 4,
  ZF = 6,
  SF,
  TF,
  IF,
  DF,
  OF,
  IOPL,
  NT,
  RF = 16,
  VM,
  AC,
  VIF,
  VIP,
  ID
};

struct GPRegister {
  uint64_t value;
  std::string name64;
  std::string name32;
  std::string name16;
  std::string name8_h = "";
  std::string name8_l = "";
};

struct SegRegister {
  uint16_t value;
  std::string name;
};

typedef uint32_t EFLAGSRegister;

class RegisterBank {
private:
  GPRegister m_gp_registers[8];
  SegRegister m_seg_registers[6];
  EFLAGSRegister m_eflags = 0x246;

public:
  RegisterBank();
  uint8_t load8(const uint32_t &index);
  uint16_t load16(const uint32_t &index);
  uint32_t load32(const uint32_t &index);
  uint64_t load64(const uint32_t &index);
  uint64_t load(const uint32_t &index, const OperandSize &size);
  void set8(const uint32_t &index, const uint8_t value);
  void set16(const uint32_t &index, const uint16_t value);
  void set32(const uint32_t &index, const uint32_t value);
  void set64(const uint32_t &index, const uint64_t value);
  void set(const uint32_t &index, const uint64_t value,
           const OperandSize &size);
  std::string name8(const uint32_t &index);
  std::string name16(const uint32_t &index);
  std::string name32(const uint32_t &index);
  std::string name64(const uint32_t &index);
  std::string name(const uint32_t &index, const OperandSize &size);
  void set_flag(const FLAG &flag, uint8_t val);
  uint8_t get_flag(const FLAG &flag);
};

#endif
