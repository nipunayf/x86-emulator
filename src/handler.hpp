#ifndef HANDLER_H
#define HANDLER_H

#include "instruction_fetcher.hpp"
#include "memory.hpp"
#include "operand.hpp"
#include "register_bank.hpp"
#include "utils.hpp"
#include <list>

#define MAX_PREFIX_COUNT 4

/**
 * Represents the state changes of a single instruction.
 */
struct Snapshot {
  std::string instruction;
  std::string byte_sequence;
  std::string reg_transition;
  std::string mem_transition;
  std::string eip_transition;
  std::list<std::string> flag_transitions;
  uint32_t start_eip;
};

/**
 * Represents an x86 instruction
 *
 */
struct Instruction {
  uint16_t opcode;
  uint8_t prefixes[MAX_PREFIX_COUNT];
  unsigned int prefixes_count : MAX_PREFIX_COUNT;
  Snapshot snapshot;
  OperandSize mode = OPERAND_32;
};

/**
 * Represents the current state of the emulator.
 */
struct State {
  InstructionFetcher &ins_fetcher;
  RegisterBank &reg_bank;
  Memory &memory;
  Instruction ins;
  std::list<Snapshot> snapshots;
};

/**
 * Represents the handler function for each opcode instruction.
 */
using Handler = void (*)(State &args);

/**
 * Add the snapshot to the queue after formatting the instruction.
 *
 * @param state current state
 * @param ins_name x86 instruction name
 * @param dest where the value is stored
 * @param source where the value is retrieved
 */
void set_snapshot(State &state, const std::string &ins_name,
                  const std::string &dest = "", const std::string &source = "");

/**
 * Set the common EFLAGS for some arithmetic instructions.
 *
 * @param state current state
 * @param op_size bit size
 * @param res output of the operation
 */
void set_common_arithmetic_flags(State &state, OperandSize op_size,
                                 uint64_t res);

/**
 * Set the common EFLAGS for some logical instructions.
 *
 * @param state current state
 * @param op_size bit size
 * @param res output of the operation
 */
void set_logical_flags(State &state, OperandSize op_size, uint64_t res);

/**
 * A template code for operations that has the MODRM byte
 */
#define MODRM_OPCODE(op_size, output, dest, ins_name, dest_name, src_name)     \
  ModRMAttribute rm_args{op_size}, reg_args{op_size};                          \
  process_modrm(state, rm_args, reg_args);                                     \
  set_value(state, dest, output);                                              \
  set_snapshot(state, ins_name, dest_name, src_name);

/**
 * A template code when the r/m is the destination.
 */
#define MODRM_DEST_OPCODE(op_size, ins_name, output)                           \
  MODRM_OPCODE(op_size, output, rm_args, ins_name, rm_args.notation,           \
               reg_args.notation)

/**
 * A template code when the r/m is the source.
 */
#define MODRM_SRC_OPCODE(op_size, ins_name, output)                            \
  MODRM_OPCODE(op_size, output, reg_args, ins_name, reg_args.notation,         \
               rm_args.notation)

/**
 * A template code when there is a immediate displacement in the instruction.
 */
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
  set_snapshot(state, ins_name, state.reg_bank.name(EAX, op_size),             \
               format_immediate(imm));

#endif
