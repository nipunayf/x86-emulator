#include "opcode.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

#define MOV_TEST_PATH (TEST_PATH + "mov/")

#define MOV(file_name, dest, expected)                                         \
  INIT_STATE(MOV_TEST_PATH + file_name)                                        \
  parse(state);                                                                \
                                                                               \
  ASSERT_EQ(dest, expected);                                                   \
  ASSERT_EQ(state.snapshots.size(), 1);

// mov al, [ebx]
TEST(MovTest, Mov8A){
  MOV("mov8A.txt", reg_bank.load8(AL), memory.load8(reg_bank.load32(EBX)))}

// mov edi, [edx + 0x12]
TEST(MovTest, Mov8B){MOV("mov8B.txt", reg_bank.load32(EDI),
                         memory.load32(reg_bank.load32(EBX) + 0X12))}

// mov %ax, %cs
TEST(MovTest,
     Mov8C){MOV("mov8C.txt", reg_bank.load16(AX), reg_bank.load_seg(CS))}

// mov %ds, [%ebx+0x12123434]
TEST(MovTest, Mov8E){MOV("mov8E.txt", reg_bank.load_seg(DS),
                         memory.load16(reg_bank.load32(EBX) + 0x12123434))}

// mov [ebx + 0x12123434], al
TEST(MovTest,
     Mov88){MOV("mov88.txt", memory.load8(reg_bank.load32(EBX) + 0x12123434),
                reg_bank.load8(AL))}

// mov ebp, esp
TEST(MovTest,
     Mov89){MOV("mov89.txt", reg_bank.load32(EBP), reg_bank.load32(ESP))}

// mov al, [0x563412c0]
TEST(MovTest,
     MovA0){MOV("movA0.txt", reg_bank.load8(AL), memory.load8(0x563412c0))}

// mov eax, [0x12123434]
TEST(MovTest,
     MovA1){MOV("movA1.txt", reg_bank.load32(EAX), memory.load8(0x12123434))}

// mov [0x57341289], al
TEST(MovTest,
     MovA2){MOV("movA2.txt", memory.load8(0x57341289), reg_bank.load8(AL))}

// mov [0x34128967], eax
TEST(MovTest,
     MovA3){MOV("movA3.txt", memory.load32(0x34128967), reg_bank.load32(EAX))}

// mov cl, 0x56
TEST(MovTest, MovB1){MOV("movB1.txt", reg_bank.load8(CL), 0X56)}

// mov esi, 0x12123434
TEST(MovTest, MovBE){MOV("movBE.txt", reg_bank.load32(ESI), 0x12123434)}

// mov [eax], 0x11
TEST(MovTest, MovC6){MOV("movC6.txt", memory.load8(reg_bank.load32(EAX)), 0x11)}

// mov [edi], 0xea679878
TEST(MovTest, MovC7) {
  MOV("movC7.txt", memory.load32(reg_bank.load32(EDI)), 0xea679878)
}
