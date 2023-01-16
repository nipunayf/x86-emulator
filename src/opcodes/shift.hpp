#ifndef OPCODE_SHIFT_H
#define OPCODE_SHIFT_H

#include "../handler.hpp"
#include "../modrm.hpp"

#define SAR_INS "sar"
#define SHR_INS "shr"
#define SAL_INS "sal"
#define SHL_INS "shl"

#define MODRM_SHIFT(op_size, T, signed_T, get_count, format_count)             \
  ModRMAttribute rm_args{op_size}, reg_args{op_size};                          \
  process_modrm(state, rm_args, reg_args);                                     \
  T count = get_count;                                                         \
  std::string operation;                                                       \
  T res;                                                                       \
  switch (reg_args.reg) {                                                      \
  case 4:                                                                      \
    operation = SAL_INS;                                                       \
    res = rm_args.val << count;                                                \
    break;                                                                     \
  case 5:                                                                      \
    operation = SHR_INS;                                                       \
    res = rm_args.val >> count;                                                \
    break;                                                                     \
  case 7:                                                                      \
    operation = SAR_INS;                                                       \
    res = (signed_T)(rm_args.val) >> count;                                    \
    break;                                                                     \
  default:                                                                     \
    break;                                                                     \
  }                                                                            \
  set_value(state, rm_args, res);                                              \
  set_shift_flags(state, op_size, operation, rm_args.val, res, count);         \
  set_snapshot(state, operation, rm_args.notation, format_count);

void shiftD0(State &state);
void shiftD1(State &state);
void shiftD3(State &state);
void shiftC0(State &state);
void shiftC1(State &state);

#endif
