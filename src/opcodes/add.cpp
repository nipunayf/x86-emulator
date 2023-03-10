#include "add.hpp"

void add00(State &state) {
  MODRM_DEST_OPCODE(OPERAND_8, ADD_INS,
                    perform_add<uint8_t>(state, OPERAND_8, (uint8_t)rm_args.val,
                                         (uint8_t)reg_args.val))
}

void add01(State &state) {
  MODRM_DEST_OPCODE(OPERAND_32, ADD_INS,
                    perform_add<int32_t>(state, OPERAND_32,
                                         (int32_t)rm_args.val,
                                         (int32_t)reg_args.val));
}

void add02(State &state) {
  MODRM_SRC_OPCODE(OPERAND_8, ADD_INS,
                   perform_add<uint8_t>(state, OPERAND_8, (uint8_t)reg_args.val,
                                        (uint8_t)rm_args.val));
}

void add03(State &state) {
  MODRM_OPCODE(OPERAND_32,
               perform_add<int32_t>(state, OPERAND_32, (int32_t)reg_args.val,
                                    (int32_t)rm_args.val),
               reg_args, ADD_INS, reg_args.notation, rm_args.notation)
}

void add04(State &state) {
  REGISTER_DISPLACEMENT_OPCODE(
    uint8_t, OPERAND_8, AL, 1, ADD_INS,
    perform_add<uint8_t>(state, OPERAND_8, reg_val, displace))
}

void add05(State &state) {
  REGISTER_DISPLACEMENT_OPCODE(
    int32_t, OPERAND_32, EAX, 4, ADD_INS,
    perform_add<int32_t>(state, OPERAND_32, reg_val, displace))
}
