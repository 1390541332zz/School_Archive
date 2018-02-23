#ifndef SIMMIPS_INSTR_HPP
#define SIMMIPS_INSTR_HPP

#include <cstddef>
#include <cstdint>
#include <array>

enum arg_type {
    UNDEF,
    OFFSET,
    LABEL,
    REG,
    MEM_DIRECT,
    MEM_INDIRECT,
    IMMEDIATE
};

struct arg 
{
    enum arg_type type = UNDEF;
    union {
        std::ptrdiff_t label;
        std::size_t reg;
        std::size_t mem_dir;
        std::size_t mem_indir;
        std::uint32_t imm;
    };
};

enum instr_type {
    LOAD_WORD,  LOAD_HALF,    LOAD_BYTE,    LOAD_IMM,   LOAD_ADD,
    STORE_WORD, STORE_HALF,   STORE_BYTE,   STORE_IMM,
    MOVE,       MOVE_FROM_HI, MOVE_FROM_LO, MOVE_TO_HI, MOVE_TO_LOW,
    ADD_S,      ADD_U,        SUB_S,        SUB_U,
    MUL,        MUL_LO,       MUL_LOU,
    MULT_S,     MULT_U,       
    DIV3_S,     DIV3_U,       DIV2_S,       DIV2_U,
    REM_S,      REM_U,
    ABS,
    NEG_S       NEG_U,
    AND,        NOR,          NOT,          OR,         XOR,
    JUMP,       BRANCH_EQ,    BRANCH_NE,
    BRANCH_LT,  BRANCH_LE,    BRANCH_GT,    BRANCH_GE,
    NOP,
    ERROR
};

class instr
{
private:
    enum instr_type op = NOP;
    std::array<arg, 3> arg;
public:
    instr();
    instr(enum instr_type type, arg a0, arg a1, arg a2);
    ~instr();
};

#endif /* SIMMIPS_INSTR_H */
