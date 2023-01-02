#include "utils.hpp"
#include <sstream>

std::string format_hex_string(uint32_t byte) {
  std::stringstream string_stream;
  string_stream << std::hex << byte;
  return "0x" + string_stream.str();
}
