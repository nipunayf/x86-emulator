#include "opcode.hpp"
#include "opcodes/add.hpp"
#include "opcodes/imm.hpp"
#include "opcodes/inc.hpp"
#include "utils.hpp"

std::map<uint8_t, Handler> handler_map{
  {0x05, add05}, {0x03, add03}, {0x40, inc4x}, {0x41, inc4x}, {0x42, inc4x},
  {0x43, inc4x}, {0x44, inc4x}, {0x45, inc4x}, {0x46, inc4x}, {0x47, inc4x},
  {0x80, imm80}, {0x81, imm81}, {0x83, imm83}};

static void set_prefix(Instruction &args, Scanner &scanner, int &index,
                       uint8_t &next_byte) {
  args.prefixes[index] = next_byte;
  index = index + 1;
  next_byte = scanner.next_byte();
}

int parse(State &state) {

  Instruction ins{};
  uint8_t next_byte = state.scanner.next_byte();
  int prefix_index = 0;

  // Repeat until the end of the file is reached
  while (next_byte > 0) {
    ins = {};
    prefix_index = 0;

    // Check for additional prefixes for opcodes > 1-byte
    if (next_byte == 0x66 || next_byte == 0xf2 || next_byte == 0xf3)
      set_prefix(ins, state.scanner, prefix_index, next_byte);

    if (prefix_index > 0 && next_byte != 0x0f)
      print_error_and_exit("Expected %s after %s",
                           format_hex_string(0x0f).c_str(),
                           format_hex_string(ins.prefixes[0]).c_str());

    // Check for opcodes > 1-byte
    if (next_byte == 0x0f) {
      set_prefix(ins, state.scanner, prefix_index, next_byte);

      // Check for 3-byte opcode
      if (next_byte == 0x38 || next_byte == 0x3a)
        set_prefix(ins, state.scanner, prefix_index, next_byte);
    }
    ins.opcode = next_byte;
    ins.prefixes_count = prefix_index;
    state.ins = ins;

    if (ins.prefixes_count > 0)
      print_error_and_exit("Invalid opcode bytes: %i is not yet supported",
                           prefix_index + 1);

    // Invoke the corresponding handler
    if (handler_map.count(ins.opcode) > 0)
      handler_map[ins.opcode](state);
    else
      print_error_and_exit("Invalid opcode: %s is not yet supported",
                           format_hex_string(ins.opcode).c_str());

    next_byte = state.scanner.next_byte();
  }

  return 0;
}
