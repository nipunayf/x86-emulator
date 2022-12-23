#include "modrm.hpp"
#include "sib.hpp"
#include <string>

uint32_t registerDirect(const uint8_t &reg, RegisterBank &regBank) {
  return regBank.load(reg);
}

uint32_t registerIndirect(const uint8_t &reg, RegisterBank &regBank,
                          Memory &memory) {
  uint32_t memAddr;
  if (reg == ESP) {
    // TODO: Replace retrieving next byte of the input
    uint8_t sib = 0xEF;
    memAddr = processSIB(sib, regBank);
  } else if (reg == EBP) {
    // TODO&CHECK: Replace retrieving next four bytes of the input
    uint32_t displacement = 0xEFEFEFEF;
    memAddr = displacement;
  } else {
    memAddr = regBank.load(reg);
  }
  return memory.read(memAddr);
}

uint32_t indirectOneByteDisplacement(const uint8_t &reg, RegisterBank &regBank,
                                     Memory &memory) {
  uint32_t memAddr;
  if (reg == ESP) {
    // TODO: Replace with retrieving the next byte of the input
    uint8_t sib = 0xEF;
    // CHECK
    uint8_t displacement = 0xEF;
    memAddr = processSIB(sib, regBank) + displacement;
  } else {
    // TODO: Replace with retrieving the next byte of the input
    uint8_t displacement = 0xEF;
    memAddr = regBank.load(reg) + displacement;
  }
  return memory.read(memAddr);
}

uint32_t indirectFourByteDisplacement(const uint8_t &reg, RegisterBank &regBank,
                                      Memory &memory) {
  uint32_t memAddr;
  if (reg == ESP) {
    // TODO: Replace retrieving next four bytes of the input
    uint8_t sib = 0xEF;
    // CHECK
    uint32_t displacement = 0xEFEFEFEF;
    memAddr = processSIB(sib, regBank) + displacement;
  } else {
    // TODO: Replace retrieving the next four bytes of the input
    uint32_t displacement = 0xEFEFEFEF;
    memAddr = regBank.load(reg) + displacement;
  }
  return memory.read(memAddr);
}

void processModRM(const uint8_t &byte, RegisterBank &regBank, Memory &memory,
                  uint32_t &operandRM, uint32_t &operandReg) {
  const uint8_t mode = byte >> 6;
  const uint8_t rm = byte & 0x07;
  const uint8_t reg = (byte >> 3) & 0x07;
  switch (mode) {
  case REGISTER_INDIRECT:
    operandRM = registerIndirect(rm, regBank, memory);
    break;
  case ONE_BYTE_DISPLACEMENT:
    operandRM = indirectOneByteDisplacement(rm, regBank, memory);
    break;
  case FOUR_BYTE_DISPLACEMENT:
    indirectFourByteDisplacement(rm, regBank, memory);
    break;
  case REGISTER_DIRECT:
    operandRM = registerDirect(rm, regBank);
    break;
  }
  operandReg = registerDirect(reg, regBank);
}
