#include "utils.hpp"
#include <sstream>

std::string format_hex_string(uint32_t byte) {
  std::stringstream string_stream;
  string_stream << std::hex << byte;
  return "0x" + string_stream.str();
}


std::string format_instruction(const std::string &operand,
                               const std::string &first_param) {
  char instruction[8];
  sprintf(instruction, "%s\t%%%s", operand.c_str(), first_param.c_str());
  return instruction;
}

std::string format_instruction(const std::string &operand,
                               const std::string &first_param,
                               const std::string &second_param) {
  char instruction[14];
  sprintf(instruction, "%s\t%%%s, %%%s", operand.c_str(), first_param.c_str(),
          second_param.c_str());
  return instruction;
}
