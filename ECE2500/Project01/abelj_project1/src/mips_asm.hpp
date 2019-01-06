#ifndef LAMBDA_MIPS_DISASM_H
#define LAMBDA_MIPS_DISASM_H
#include <cstdint>
#include <vector>

struct instr {
    std::uint8_t op = 0;
    std::uint8_t func = 0;
    std::uint8_t rs = 0;
    std::uint8_t rt = 0;
    std::uint8_t rd = 0;
    std::uint8_t sh = 0;
    std::int32_t imm = 0;
    std::uint32_t addr = 0;
};

struct mips {
    std::vector<instr> instrs;
    std::vector<std::size_t> labels;
};

#endif /* LAMBDA_MIPS_DISASM_H */
