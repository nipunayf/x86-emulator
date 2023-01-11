#include "sub.hpp"

void sub28(State &state) {
  MODRM_DEST_OPCODE(state, OPERAND_8, SUB_INS,
                    perform_sub<int8_t>(state, OPERAND_8, (int8_t)rm_args.val,
                                        (int8_t)reg_args.val))
}

void sub29(State &state) {
  MODRM_DEST_OPCODE(state, OPERAND_32, SUB_INS,
                    perform_sub<int32_t>(state, OPERAND_32,
                                         (int32_t)rm_args.val,
                                         (int32_t)reg_args.val));
}

void sub2A(State &state) {
  MODRM_SRC_OPCODE(state, OPERAND_8, SUB_INS,
                   perform_sub<int8_t>(state, OPERAND_8, (int8_t)reg_args.val,
                                       (int8_t)rm_args.val));
}

void sub2B(State &state) {
  MODRM_OPCODE(state, OPERAND_32,
               perform_sub<int32_t>(state, OPERAND_32, (int32_t)reg_args.val,
                                    (int32_t)rm_args.val),
               reg_args, SUB_INS, reg_args.notation, rm_args.notation)
}

void sub2C(State &state) {
  REGISTER_DISPLACEMENT_OPCODE(
    state, int8_t, OPERAND_8, AL, 1, SUB_INS,
    perform_sub<int8_t>(state, OPERAND_8, reg_val, displace))
}

void sub2D(State &state) {
  REGISTER_DISPLACEMENT_OPCODE(
    state, int32_t, OPERAND_32, EAX, 4, SUB_INS,
    perform_sub<int32_t>(state, OPERAND_32, reg_val, displace))
}
