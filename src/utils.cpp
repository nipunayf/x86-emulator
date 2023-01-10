#include "utils.hpp"
#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <sstream>

std::string format_hex_string(uint32_t byte) {
  std::stringstream string_stream;
  string_stream << std::hex << byte;
  return "0x" + string_stream.str();
}

std::string format_instruction(const std::string &operand,
                               const std::string &first_param) {
  const unsigned short len = operand.length() + first_param.length() + 1;
  char instruction[len];
  sprintf(instruction, "%s\t%s", operand.c_str(), first_param.c_str());
  return instruction;
}

std::string format_instruction(const std::string &operand,
                               const std::string &first_param,
                               const std::string &second_param) {
  const unsigned short len =
    operand.length() + first_param.length() + second_param.length() + 3;
  char instruction[len];
  sprintf(instruction, "%s\t%s, %s", operand.c_str(), first_param.c_str(),
          second_param.c_str());
  return instruction;
}

std::string format_register_change(const std::string &reg_name,
                                   uint32_t prev_value, uint32_t after_value) {
  char change[77];
  sprintf(change, "%s(%s) -> (%s)", reg_name.c_str(),
          format_hex_string(prev_value).c_str(),
          format_hex_string(after_value).c_str());
  return change;
}

std::string format_immediate(uint32_t immediate) {
  return std::to_string(immediate);
}

std::string format_sib(const std::string &base, const std::string &index,
                       const uint8_t &scale, const uint32_t displacement) {
  std::string optional = "";
  if (scale > 1)
    optional = "*" + std::to_string(scale);
  if (displacement)
    optional = "+" + std::to_string(displacement);
  const unsigned short len =
    base.length() + index.length() + optional.length() + 6;
  char addr[len];
  sprintf(addr, "[%s+%s%s]", base.c_str(), index.c_str(), optional.c_str());
  return addr;
}

std::string format_indirect_register(const std::string reg) {
  return "[" + reg + "]";
}

std::string format_indirect_with_displacement(const std::string reg,
                                              uint32_t memory_addr) {
  return "[" + reg + "+" + format_hex_string(memory_addr) + "]";
}

std::string format_memory_address(uint32_t memory_addr) {
  return "[" + format_hex_string(memory_addr) + "]";
}

void print_error_and_exit(const std::string &format, ...) {
  va_list args;
  va_start(args, format);
  int size = vsnprintf(nullptr, 0, format.c_str(), args) + 1;
  va_start(args, format);
  char msg[size];
  vsnprintf(msg, size, format.c_str(), args);
  std::cerr << msg << std::endl;
  va_end(args);
  exit(1);
}

uint8_t read_msb(uint8_t op_size, uint64_t value) {
  return (value & (1ull << (8 * (2 ^ op_size) - 1))) > 0;
}
