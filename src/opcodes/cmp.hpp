#ifndef OPCODE_CMP_H
#define OPCODE_CMP_H

#include "../handler.hpp"
#include "../modrm.hpp"

#define CMP_INS "cmp"

#define MODRM_CMP(op_size, T, src, dest, src_name, dest_name)                  \
  ModRMAttribute rm_args{op_size}, reg_args{op_size};                          \
  process_modrm(state, rm_args, reg_args);                                     \
  perform_sub<T>(state, op_size, src, dest);                                   \
  set_snapshot(state, CMP_INS, src_name, dest_name);

#define MODRM_CMP_SRC(op_size, T)                                              \
  MODRM_CMP(op_size, T, rm_args.val, reg_args.val, rm_args.notation,           \
            reg_args.notation)

#define MODRM_CMP_DEST(op_size, T)                                             \
  MODRM_CMP(op_size, T, reg_args.val, rm_args.val, reg_args.notation,          \
            rm_args.notation)

void cmp3C(State &state);
void cmp3D(State &state);
void cmp38(State &state);
void cmp39(State &state);
void cmp3A(State &state);
void cmp3B(State &state);

#endif
