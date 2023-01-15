#include "sbb.hpp"

void sbb18(State &state) {
  MODRM_DEST_OPCODE(OPERAND_8, SBB_INS,
                    perform_sbb<uint8_t>(state, OPERAND_8, (uint8_t)rm_args.val,
                                         (uint8_t)reg_args.val))
}

void sbb19(State &state) {
  MODRM_DEST_OPCODE(OPERAND_32, SBB_INS,
                    perform_sbb<uint32_t>(state, OPERAND_32,
                                          (uint32_t)rm_args.val,
                                          (uint32_t)reg_args.val));
}

void sbb1A(State &state) {
  MODRM_SRC_OPCODE(OPERAND_8, SBB_INS,
                   perform_sbb<uint8_t>(state, OPERAND_8, (uint8_t)reg_args.val,
                                        (uint8_t)rm_args.val));
}

void sbb1B(State &state) {
  MODRM_OPCODE(OPERAND_32,
               perform_sbb<uint32_t>(state, OPERAND_32, (uint32_t)reg_args.val,
                                     (uint32_t)rm_args.val),
               reg_args, SBB_INS, reg_args.notation, rm_args.notation)
}

void sbb1C(State &state) {
  REGISTER_DISPLACEMENT_OPCODE(
    uint8_t, OPERAND_8, AL, 1, SBB_INS,
    perform_sbb<uint8_t>(state, OPERAND_8, reg_val, displace))
}

void sbb1D(State &state) {
  REGISTER_DISPLACEMENT_OPCODE(
    uint32_t, OPERAND_32, EAX, 4, SBB_INS,
    perform_sbb<uint32_t>(state, OPERAND_32, reg_val, displace))
}
