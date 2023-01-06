#include "opcode.hpp"
#include "utils.hpp"
#include <iostream>

std::map<uint8_t, Handler> handler_map{
  {0x40, inc4x}, {0x41, inc4x}, {0x42, inc4x}, {0x43, inc4x},
  {0x44, inc4x}, {0x45, inc4x}, {0x46, inc4x}, {0x47, inc4x}};

static void set_prefix(Argument &args, Scanner &scanner, int &index,
                       uint8_t &next_byte) {
  args.prefixes[index] = next_byte;
  index = index + 1;
  next_byte = scanner.next_byte();
}

int parse(State &state) {

  Argument args;
  uint8_t next_byte = state.scanner.next_byte();
  int prefix_index = 0;

  // Repeat until the end of the file is reached
  while (next_byte > 0) {
    args = {};
    prefix_index = 0;

    // Check for additional prefixes for opcodes > 1-byte
    if (next_byte == 0x66 || next_byte == 0xf2 || next_byte == 0xf3)
      set_prefix(args, state.scanner, prefix_index, next_byte);

    if (prefix_index > 0 && next_byte != 0x0f) {
      char err_msg[17];
      sprintf(err_msg, "Expected %s after %s", format_hex_string(0x0f).c_str(),
              format_hex_string(args.prefixes[0]).c_str());
      std::cerr << err_msg << std::endl;
      exit(1);
    }

    // Check for opcodes > 1-byte
    if (next_byte == 0x0f) {
      set_prefix(args, state.scanner, prefix_index, next_byte);

      // Check for 3-byte opcode
      if (next_byte == 0x38 || next_byte == 0x3a)
        set_prefix(args, state.scanner, prefix_index, next_byte);
    }
    args.opcode = next_byte;
    args.prefixes_count = prefix_index;
    state.args = args;

    if (args.prefixes_count > 0) {
      char err_msg[45];
      sprintf(err_msg, "Invalid opcode bytes: %i is not yet supported",
              prefix_index + 1);
      std::cerr << err_msg << std::endl;
      exit(1);
    }

    // Invoke the corresponding handler
    if (handler_map.count(args.opcode) > 0)
      handler_map[args.opcode](state);
    else {
      char err_msg[38];
      sprintf(err_msg, "Invalid opcode: %s is not yet supported",
              format_hex_string(args.opcode).c_str());
      std::cerr << err_msg << std::endl;
      exit(1);
    }

    next_byte = state.scanner.next_byte();
  }

  return 0;
}
