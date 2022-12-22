#include "modrm.hpp"
#include <iostream>
#include <string>

void registerDirect(int reg, RegisterBank regBank) {
    std::cout << "register direct addressing method: "
              << regBank.loadRegisterValue(reg) << std::endl;
}

void registerIndirect(int reg, RegisterBank regBank) {
    std::cout << "register indirect addressing: ";
    if (reg == ESP)
        std::cout << "accessing the SIB byte" << std::endl;
    else if (reg == EBP)
        std::cout << "displacement of 32 bits" << std::endl;
    else
        std::cout << "loading from memory address: "
                  << regBank.loadRegisterValue(reg) << std::endl;
}

void indirectOneByteDisplacement(int reg, RegisterBank regBank) {
    std::cout << "indirect one byte addressing method" << std::endl;
    if (reg == ESP)
        std::cout << "accessing the SIB byte" << std::endl;
    else
        std::cout << "loading from memory address and 8 bit displacement: "
                  << regBank.loadRegisterValue(reg) << std::endl;
}

void indirectFourByteDisplacement(int reg, RegisterBank regBank) {
    std::cout << "indirect one byte addressing method" << std::endl;
    if (reg == ESP)
        std::cout << "accessing the SIB byte" << std::endl;
    else
        std::cout << "loading from memory address and 8 bit displacement: "
                  << regBank.loadRegisterValue(reg) << std::endl;
}

int processModRM(int byte, RegisterBank regBank) {
    int mode = byte >> 6;
    int rm   = byte & 0x07;
    int reg  = (byte >> 3) & 0x07;
    std::cout << "val:" << byte << std::endl;
    std::cout << "mode:" << mode << std::endl;
    std::cout << "rm:" << rm << std::endl;
    std::cout << "reg:" << reg << std::endl;
    switch (mode) {
    case 0:
        registerIndirect(rm, regBank);
        break;
    case 1:
        indirectOneByteDisplacement(rm, regBank);
        break;
    case 2:
        indirectFourByteDisplacement(rm, regBank);
        break;
    case 3:
        registerDirect(rm, regBank);
        break;
    }
    return 0;
}
