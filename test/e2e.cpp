#include "parse.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define E2E_TEST_PATH (TEST_PATH + "e2e/")

#define E2E_TEST(file_name, assertion, num_snapshots)                          \
  INIT_STATE(E2E_TEST_PATH + file_name)                                        \
  RegisterBank original_reg_bank = reg_bank;                                   \
  parse(state);                                                                \
                                                                               \
  assertion;                                                                   \
  ASSERT_EQ(state.snapshots.size(), num_snapshots);

// int n = 10;
// int old = 0;
// int prev = 1;
// int fib;
// for (int i = 2; i <= n; i++) {
//   fib = prev + old;
//   old = prev;
//   prev = fib;
// }
// push ebp
// mov ebp, esp
// mov dword ptr [ebp - 0x10], 9
// mov dword ptr [ebp - 4], 0
// mov dword ptr [ebp - 8], 1
// mov dword ptr [ebp - 0xc], 2
// jmp 0x3c
// mov edx, dword ptr [ebp - 8]
// mov eax, dword ptr [ebp - 4]
// add eax, edx
// mov dword ptr [ebp - 0x14], eax
// mov eax, dword ptr [ebp - 8]
// mov dword ptr [ebp - 4], eax
// mov eax, dword ptr [ebp - 0x14]
// mov dword ptr [ebp - 8], eax
// add dword ptr [ebp - 0xc], 1
// mov eax, dword ptr [ebp - 0xc]
// cmp eax, dword ptr [ebp - 0x10]
// jle 0x21
// mov eax, dword ptr [ebp - 0x14]
// pop ebp
// fib(9) = 34 (0x22)
TEST(E2ETest, FibonacciSequence){
  E2E_TEST("fib.txt", ASSERT_EQ(reg_bank.load32(EAX), 0x22), 108)}

// mov ebx, 0xfa301020
// add ebx, 0xca120312
// mov eax, 0xac302102
// adc eax, 0x10ac021
// sub ebx, 0xca120312
// sbb eax, 0x10ac021
// xor ebx, 0xfa301020
// xor eax, 0xac302102
TEST(E2ETest, Arithmetic64Bit) {
  E2E_TEST("arithmetic_64bit.txt", ASSERT_EQ(reg_bank.load32(EAX), 0);
           ASSERT_EQ(reg_bank.load32(EBX), 0), 8)
}