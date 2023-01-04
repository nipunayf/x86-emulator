#ifndef UTILS_H
#define UTILS_H

#include <string>

std::string format_hex_string(uint32_t byte);

std::string format_instruction(const std::string &operand,
                               const std::string &first_param);

std::string format_instruction(const std::string &operand,
                               const std::string &first_param,
                               const std::string &second_param);

#endif
