#ifndef UTILS_H
#define UTILS_H

#include <string>

#define MASK8 255

std::string format_hex_string(uint32_t byte);

std::string format_instruction(const std::string &operand,
                               const std::string &first_param);

std::string format_instruction(const std::string &operand,
                               const std::string &first_param,
                               const std::string &second_param);

std::string format_register_change(const std::string &reg_name,
                                   uint32_t before_value, uint32_t after_value);

std::string format_immediate(uint32_t immediate);

std::string format_base_index(const std::string &base,
                              const std::string &index);

std::string format_sib(const std::string &base, const std::string &index,
                       const uint8_t &scale, uint32_t displacement);

std::string format_indirect_register(const std::string& reg);

std::string format_memory_address(uint32_t memory_addr);

std::string format_indirect_with_displacement(const std::string& reg,
                                              uint32_t memory_addr);

void print_error_and_exit(const std::string &format, ...);

uint8_t read_msb(uint8_t op_size, uint64_t value);

#endif
