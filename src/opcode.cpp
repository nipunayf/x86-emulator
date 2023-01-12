#include "opcode.hpp"
#include "opcodes/adc.hpp"
#include "opcodes/add.hpp"
#include "opcodes/dec.hpp"
#include "opcodes/extension.hpp"
#include "opcodes/inc.hpp"
#include "opcodes/move.hpp"
#include "opcodes/pop.hpp"
#include "opcodes/push.hpp"
#include "opcodes/sbb.hpp"
#include "opcodes/sub.hpp"
#include "opcodes/xchg.hpp"
#include "utils.hpp"

std::map<uint16_t, Handler> handler_map{
  {0x00, add00},     {0x01, add01},    {0x02, add02},      {0x03, add03},
  {0x04, add04},     {0x05, add05},    {0x10, adc10},      {0x11, adc11},
  {0x12, adc12},     {0x13, adc13},    {0x14, adc14},      {0x15, adc15},
  {0x18, sbb18},     {0x19, sbb19},    {0x1a, sbb1A},      {0x1b, sbb1B},
  {0x1c, sbb1C},     {0x1d, sbb1D},    {0x28, sub28},      {0x29, sub29},
  {0x2a, sub2A},     {0x2b, sub2B},    {0x2c, sub2C},      {0x2d, sub2D},
  {0x40, inc4x},     {0x41, inc4x},    {0x42, inc4x},      {0x43, inc4x},
  {0x44, inc4x},     {0x45, inc4x},    {0x46, inc4x},      {0x47, inc4x},
  {0x48, dec4x},     {0x49, dec4x},    {0x4a, dec4x},      {0x4b, dec4x},
  {0x4c, dec4x},     {0x4d, dec4x},    {0x4e, dec4x},      {0x4f, dec4x},
  {0x50, push5x},    {0x51, push5x},   {0x52, push5x},     {0x53, push5x},
  {0x54, push5x},    {0x55, push5x},   {0x56, push5x},     {0x57, push5x},
  {0x6A, push6A},    {0x68, push68},   {0x0E, push0E},     {0x16, push16},
  {0x1E, push1E},    {0x06, push06},   {0x0FA0, push0FA0}, {0x0FA8, push0FA8},
  {0x58, pop5x},     {0x59, pop5x},    {0x5A, pop5x},      {0x5B, pop5x},
  {0x5C, pop5x},     {0x5D, pop5x},    {0x5E, pop5x},      {0x5F, pop5x},
  {0x1F, pop1F},     {0x07, pop07},    {0x17, pop17},      {0x0FA1, pop0FA1},
  {0x0FA9, pop0FA9}, {0x88, mov88},    {0x89, mov89},      {0x8A, mov8A},
  {0x8B, mov8B},     {0x8C, mov8C},    {0x8E, mov8E},      {0xA0, movA0_A1},
  {0xA1, movA0_A1},  {0xA2, movA2_A3}, {0xA3, movA2_A3},   {0xB0, movBx},
  {0xB1, movBx},     {0xB2, movBx},    {0xB3, movBx},      {0xB4, movBx},
  {0xB5, movBx},     {0xB6, movBx},    {0xB7, movBx},      {0xB8, movBx},
  {0xB9, movBx},     {0xBA, movBx},    {0xBB, movBx},      {0xBC, movBx},
  {0xBD, movBx},     {0xBE, movBx},    {0xBF, movBx},      {0xC6, movCx},
  {0xC7, movCx},     {0x80, ext80},    {0x81, ext81},      {0x83, ext83},
  {0xFE, extFE},     {0xFF, extFF},    {0x8F, ext8F},      {0x86, xchg86_87},
  {0x87, xchg86_87}, {0x91, xchg9x},   {0x92, xchg9x},     {0x93, xchg9x},
  {0x94, xchg9x},    {0x95, xchg9x},   {0x96, xchg9x},     {0x97, xchg9x}};

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
  while (!state.scanner.is_eof()) {
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
