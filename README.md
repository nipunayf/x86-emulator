# x86-emulator

[![Windows Build](https://github.com/nipunayf/x86-emulator/actions/workflows/ubuntu-build.yml/badge.svg)](https://github.com/nipunayf/x86-emulator/actions/workflows/ci.yml)
[![Ubuntu Build](https://github.com/nipunayf/x86-emulator/actions/workflows/windows-build.yml/badge.svg)](https://github.com/nipunayf/x86-emulator/actions/workflows/windows-build.yml)
[![Format](https://github.com/nipunayf/x86-emulator/actions/workflows/clang-format.yml/badge.svg)](https://github.com/nipunayf/x86-emulator/actions/workflows/clang-format.yml)
[![codecov](https://codecov.io/gh/nipunayf/x86-emulator/branch/main/graph/badge.svg?token=XSN85EWGF2)](https://codecov.io/gh/nipunayf/x86-emulator)

x86 emulator to simulate basic operations
Currently, the emulator supports the following instruction set,
- Logical instructions (AND, OR. XOR, NOT)
- Control transfer instructions (JMP, Jcc)
- Stack instructions (PUSH, POP)
- Arithmetic instructions (ADD, ADC, SUB, SBB, INC, DEC)
- Shift instructions (SAL, SAR, SHL, SHR)
- Comparative instructions (CMP, TEST)
- Flag control instructions (STC, CLC, CMC)
- Miscellaneous instructions (NOP, LEA)




## Installation

Install the root directory of the project execute following commands.

```bash
  cmake -B build
  cmake --build build
```

## Usage/Examples
After following the installation instructions the executable generated will be inside the folder `build/src/`.
To emulate an object file using the emulator while inside the parent directory of the project execute the following command.

```bash
  ./build/src/emulator <path-to-object-file>

```


## Running Tests


The test scripts are within the `test` directory in root and the executables for tests are inside the directory `build/test/`

To run the entire test suite of the emulator,
```bash
  ctest --test-dir build --parallel
```
To run a test execute the following command,
```bash
  ctest --test-dir build -R <test-name>
```
To execute end to end tests runs,
```bash
  ctest --test-dir build -R E2E
```
