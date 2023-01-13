#include "opcode.hpp"
#include "opcodes/adc.hpp"
#include "opcodes/add.hpp"
#include "opcodes/and.hpp"
#include "opcodes/cmp.hpp"
#include "opcodes/dec.hpp"
#include "opcodes/extension.hpp"
#include "opcodes/flags.hpp"
#include "opcodes/inc.hpp"
#include "opcodes/jmp.hpp"
#include "opcodes/lea.hpp"
#include "opcodes/move.hpp"
#include "opcodes/nop.hpp"
#include "opcodes/or.hpp"
#include "opcodes/pop.hpp"
#include "opcodes/push.hpp"
#include "opcodes/sbb.hpp"
#include "opcodes/shift.hpp"
#include "opcodes/sub.hpp"
#include "opcodes/test.hpp"
#include "opcodes/xchg.hpp"
#include "opcodes/xor.hpp"
#include "utils.hpp"

std::map<uint16_t, Handler> one_handler_map{
  {0x00, add00},     {0x01, add01},     {0x02, add02},     {0x03, add03},
  {0x04, add04},     {0x05, add05},     {0x10, adc10},     {0x11, adc11},
  {0x12, adc12},     {0x13, adc13},     {0x14, adc14},     {0x15, adc15},
  {0x18, sbb18},     {0x19, sbb19},     {0x1a, sbb1A},     {0x1b, sbb1B},
  {0x1c, sbb1C},     {0x1d, sbb1D},     {0x28, sub28},     {0x29, sub29},
  {0x2a, sub2A},     {0x2b, sub2B},     {0x2c, sub2C},     {0x2d, sub2D},
  {0x40, inc4x},     {0x41, inc4x},     {0x42, inc4x},     {0x43, inc4x},
  {0x44, inc4x},     {0x45, inc4x},     {0x46, inc4x},     {0x47, inc4x},
  {0x48, dec4x},     {0x49, dec4x},     {0x4a, dec4x},     {0x4b, dec4x},
  {0x4c, dec4x},     {0x4d, dec4x},     {0x4e, dec4x},     {0x4f, dec4x},
  {0x50, push5x},    {0x51, push5x},    {0x52, push5x},    {0x53, push5x},
  {0x54, push5x},    {0x55, push5x},    {0x56, push5x},    {0x57, push5x},
  {0x6A, push6A},    {0x68, push68},    {0x90, nop90},     {0x0E, push0E},
  {0x16, push16},    {0x1E, push1E},    {0x06, push06},    {0x58, pop5x},
  {0x59, pop5x},     {0x5A, pop5x},     {0x5B, pop5x},     {0x5C, pop5x},
  {0x5D, pop5x},     {0x5E, pop5x},     {0x5F, pop5x},     {0x1F, pop1F},
  {0x07, pop07},     {0x17, pop17},     {0x88, mov88},     {0x89, mov89},
  {0x8A, mov8A},     {0x8B, mov8B},     {0x8C, mov8C},     {0x8E, mov8E},
  {0xA0, movA0_A1},  {0xA1, movA0_A1},  {0xA2, movA2_A3},  {0xA3, movA2_A3},
  {0xB0, movBx},     {0xB1, movBx},     {0xB2, movBx},     {0xB3, movBx},
  {0xB4, movBx},     {0xB5, movBx},     {0xB6, movBx},     {0xB7, movBx},
  {0xB8, movBx},     {0xB9, movBx},     {0xBA, movBx},     {0xBB, movBx},
  {0xBC, movBx},     {0xBD, movBx},     {0xBE, movBx},     {0xBF, movBx},
  {0xC6, movCx},     {0xC7, movCx},     {0x3C, cmp3C},     {0x3D, cmp3D},
  {0x38, cmp38},     {0x39, cmp39},     {0x3A, cmp3A},     {0x3B, cmp3B},
  {0xA8, testA8_A9}, {0xA9, testA8_A9}, {0x84, test84_85}, {0x85, test84_85},
  {0x80, ext80},     {0x81, ext81},     {0x83, ext83},     {0xEB, jmpEB},
  {0xF5, cmc},       {0xF8, clc},       {0xF9, stc},       {0xFE, extFE},
  {0xFF, extFF},     {0x8F, ext8F},     {0xF6, extF6},     {0xF7, extF7},
  {0x86, xchg86_87}, {0x87, xchg86_87}, {0x91, xchg9x},    {0x92, xchg9x},
  {0x93, xchg9x},    {0x94, xchg9x},    {0x95, xchg9x},    {0x96, xchg9x},
  {0x97, xchg9x},    {0xD0, shiftD0},   {0xD1, shiftD1},   {0xD3, shiftD3},
  {0xC0, shiftC0},   {0xC1, shiftC1},   {0x8D, lea8D},     {0x24, and24},
  {0x25, and25},     {0x20, and20},     {0x21, and21},     {0x22, and22},
  {0x23, and23},     {0x0C, or0C},      {0x0D, or0D},      {0x08, or08},
  {0x09, or09},      {0x0A, or0A},      {0x0B, or0B},      {0x34, xor34},
  {0x35, xor35},     {0x30, xor30},     {0x31, xor31},     {0x32, xor32},
  {0x33, xor33}};

std::map<uint16_t, Handler> two_handler_map = {{0x1F, nop0F1F},
                                               {0xA0, push0FA0},
                                               {0xA1, pop0FA1},
                                               {0xA8, push0FA8},
                                               {0xA9, pop0FA9}};

static void set_prefix(Instruction &args, State &state, int &index,
                       uint8_t &next_byte) {
  args.prefixes[index] = next_byte;
  index = index + 1;
  next_byte = state.ins_fetcher.next_byte();
}

int parse(State &state) {
  Instruction ins{};
  uint8_t next_byte = state.ins_fetcher.next_byte();
  int prefix_index = 0;
  std::map<uint16_t, Handler> handler_map = one_handler_map;

  // Repeat until the end of the file is reached
  while (!state.ins_fetcher.is_eof()) {
    ins = {};
    ins.start_eip = state.reg_bank.load_eip() - 1;
    prefix_index = 0;

    // Check for additional prefixes for opcodes > 1-byte
    if (next_byte == 0x66 || next_byte == 0xf2 || next_byte == 0xf3)
      set_prefix(ins, state, prefix_index, next_byte);

    // Check for opcodes > 1-byte
    if (next_byte == 0x0f) {
      set_prefix(ins, state, prefix_index, next_byte);
      handler_map = two_handler_map;

      // Check for 3-byte opcode
      if (next_byte == 0x38 || next_byte == 0x3a)
        print_error_and_exit("3-byte opcode bytes are not yet supported",
                             prefix_index + 1);
    }
    ins.opcode = next_byte;
    ins.prefixes_count = prefix_index;
    state.ins = ins;

    // Invoke the corresponding handler
    if (handler_map.count(ins.opcode) > 0)
      handler_map[ins.opcode](state);
    else
      print_error_and_exit("Invalid opcode: %s is not yet supported",
                           format_hex_string(ins.opcode).c_str());

    next_byte = state.ins_fetcher.next_byte();
    handler_map = one_handler_map;
  }

  return 0;
}
