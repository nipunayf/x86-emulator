#ifndef UTILS_H
#define UTILS_H

#include <string>

std::string format_hex_string(uint32_t byte);

std::string format_instruction(const std::string &operand,
                               const std::string &first_param);

std::string format_instruction(const std::string &operand,
                               const std::string &first_param,
                               const std::string &second_param);

std::string format_register_change(const std::string &reg_name,
                                   uint32_t before_value, uint32_t after_value);

std::string format_displacement(uint32_t memory_addr);

#endif
