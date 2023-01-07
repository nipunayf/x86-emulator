#include "utils.hpp"
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
                                   uint32_t before_value,
                                   uint32_t after_value) {
  char change[77];
  sprintf(change, "%s(%s) -> (%s)", reg_name.c_str(),
          format_hex_string(before_value).c_str(),
          format_hex_string(after_value).c_str());
  return change;
}

std::string format_displacement(uint32_t memory_addr) {
  return "$" + format_hex_string(memory_addr);
}
