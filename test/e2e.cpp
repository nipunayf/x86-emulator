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

// lea ecx, [esp + 4]
// and esp, 0xfffffff0
// push eax
// sar eax, 2
// xor al, 0x2e
// mov ebp, esp
// inc ebp
// sub esp, 4
// cmp [esp + 4], 0x81
// pop ebp
TEST(E2ETest, Sample) {
  E2E_TEST("sample.txt", ASSERT_EQ(reg_bank.load32(EBP), 0x0);
           ASSERT_EQ(reg_bank.load32(ESP), 0xbf8d00ac);
           ASSERT_EQ(reg_bank.load32(ECX), 0xbf8db0c0);, 10)
}

//  int x = 100, y = -100;
//  bool z = ((x ^ y) < 0);
// push ebp
// dec eax
// mov ebp, esp
// mov dword ptr [ebp - 4], 0x64
// mov dword ptr [ebp - 8], 0xffffff9c
// mov eax, dword ptr [ebp - 4]
// xor eax, dword ptr [ebp - 8]
// shr eax, 0x1f
TEST(E2ETest,
     SignCheck){E2E_TEST("sign.txt", ASSERT_EQ(reg_bank.load32(EAX), 0x1), 9)}

// int n = 32;
// bool is_power = false;
// if (n && (!(n & (n - 1)))) {
// is_power = true;
// }
// push ebp
// mov ebp, esp
// mov dword ptr [ebp - 4], 0x20
// mov byte ptr [ebp - 5], 0
// cmp dword ptr [ebp - 4], 0
// je 0x25
// mov eax, dword ptr [ebp - 4]
// sub eax, 1
// and eax, dword ptr [ebp - 4]
// test eax, eax
// jne 0x25
// mov byte ptr [ebp - 5], 1
// mov eax, 0
// pop ebp
TEST(E2ETest, Pow2) {
  E2E_TEST("pow2.txt", ASSERT_EQ(memory.load32(0xbf8db0b3), 0x1), 14)
}
