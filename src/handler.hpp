#ifndef HANDLER_H
#define HANDLER_H

#include "instruction_fetcher.hpp"
#include "memory.hpp"
#include "operand.hpp"
#include "register_bank.hpp"
#include "utils.hpp"
#include <list>

#define MAX_PREFIX_COUNT 4

struct Snapshot {
  std::string instruction;
  std::string byte_sequence;
  std::string reg_transition;
  std::string mem_transition;
  std::string eip_transition;
  std::list<std::string> flag_transitions;
  uint32_t eip;
};

struct Instruction {
  uint16_t opcode;
  uint8_t prefixes[MAX_PREFIX_COUNT];
  unsigned int prefixes_count : MAX_PREFIX_COUNT;
  uint32_t start_eip;
  Snapshot snapshot;
};

// Default mode is 32 bit and this can be changed to 16 bit with instruction
// prefixes "0x66"
struct State {
  InstructionFetcher &ins_fetcher;
  RegisterBank &reg_bank;
  Memory &memory;
  Instruction ins;
  std::list<Snapshot> snapshots;
  OperandSize mode = OPERAND_32;
};

using Handler = void (*)(State &args);

void set_snapshot(State &state, const std::string &ins_name,
                  const std::string &dest = "", const std::string &source = "");

void set_common_arithmetic_flags(State &state, OperandSize op_size,
                                 uint64_t res);

void set_logical_flags(State &state, OperandSize op_size, uint64_t res);

#define MODRM_OPCODE(op_size, output, dest, ins_name, dest_name, src_name)     \
  ModRMAttribute rm_args{op_size}, reg_args{op_size};                          \
  process_modrm(state, rm_args, reg_args);                                     \
  set_value(state, dest, output);                                              \
  set_snapshot(state, ins_name, dest_name, src_name);

#define MODRM_DEST_OPCODE(op_size, ins_name, output)                           \
  MODRM_OPCODE(op_size, output, rm_args, ins_name, reg_args.notation,          \
               rm_args.notation)

#define MODRM_SRC_OPCODE(op_size, ins_name, output)                            \
  MODRM_OPCODE(op_size, output, reg_args, ins_name, rm_args.notation,          \
               reg_args.notation)

#define REGISTER_DISPLACEMENT_OPCODE(op_type, op_size, reg, displace_bytes,    \
                                     ins_name, output)                         \
  auto reg_val = (op_type)state.reg_bank.load(reg, op_size);                   \
  auto displace = (op_type)state.ins_fetcher.next_nbytes(displace_bytes);      \
  state.reg_bank.set(state.ins.snapshot.reg_transition, reg, output, op_size); \
  set_snapshot(state, ins_name, state.reg_bank.name(reg, op_size),             \
               format_immediate(displace));

#define IMM_EAX_OPCODE(op_size, T, ins_name, output)                           \
  T imm = state.ins_fetcher.next_nbytes(1 << op_size);                         \
  T reg_val = state.reg_bank.load(EAX, op_size);                               \
  state.reg_bank.set(state.ins.snapshot.reg_transition, EAX, output, op_size); \
  set_snapshot(state, ins_name, format_immediate(imm),                         \
               state.reg_bank.name(EAX, op_size));

#endif
