#ifndef OPCODE_TEST_H
#define OPCODE_TEST_H

#include "../handler.hpp"
#include "../modrm.hpp"

#define TEST_INS "test"

void testA8_A9(State &state);
void test84_85(State &state);
void perform_test(State &state, OperandSize op_size, uint32_t op1,
                  uint32_t op2);

#endif
