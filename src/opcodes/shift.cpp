#include "shift.hpp"
#include <string.h>
void set_shift_flags(State &state, OperandSize size, std::string operation,
                     uint32_t val, uint32_t res, uint32_t count) {
  const uint8_t cf = strcmp(operation.c_str(), SAL_INS)
                       ? (val >> (count - 1)) & 1ul
                       : read_msb(size, val << (count - 1));
  if (count != 0)
    state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, CF, cf);
  if (count == 1)
    state.reg_bank.set_flag(state.ins.snapshot.flag_transitions, OF,
                            read_msb(size, res) == cf ? 0 : 1);
}

void shiftD0(State &state) {
  MODRM_SHIFT(OPERAND_8, uint8_t, int8_t, 1, format_immediate(1))
}

void shiftD2(State &state) {
  MODRM_SHIFT(OPERAND_8, uint8_t, int8_t, state.reg_bank.load8(CL),
              state.reg_bank.name8(CL))
}

void shiftC0(State &state) {
  MODRM_SHIFT(OPERAND_8, uint8_t, int8_t,
              state.scanner.next_byte(state.reg_bank, state.mode),
              format_immediate(count))
}

void shiftD1(State &state) {
  MODRM_SHIFT(OPERAND_32, uint32_t, int32_t, 1, format_immediate(1))
}

void shiftD3(State &state) {
  MODRM_SHIFT(OPERAND_32, uint32_t, int32_t, state.reg_bank.load8(CL),
              state.reg_bank.name8(CL))
}

void shiftC1(State &state) {
  MODRM_SHIFT(OPERAND_32, uint32_t, int32_t,
              state.scanner.next_byte(state.reg_bank, state.mode),
              format_immediate(count))
}
