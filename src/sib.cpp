#include "sib.hpp"
#include "register_bank.hpp"
#include <iostream>
#include <cmath>

int getScaledIndex(int scale, int index, RegisterBank regBank) {
    if (index == ESP) {
        fprintf(stderr, "Register esp cannot be the index of the SIB byte");
        exit(1);
    }
    return regBank.loadRegisterValue(index) * pow(2, scale);
}
int processSIB(int byte, RegisterBank regBank) {
    int base = byte & 0x07;
    int index   = (byte >> 3) & 0x07;
    int scale  = (byte >> 6) & 0x03;
    std::cout << "val:" << byte << std::endl;
    std::cout << "scaled index:" << getScaledIndex(scale, index, regBank) << std::endl;
    int memAddr = regBank.loadRegisterValue(base) + getScaledIndex(scale, index, regBank);
}
