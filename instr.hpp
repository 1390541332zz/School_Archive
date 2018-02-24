#ifndef SIMMIPS_INSTR_HPP
#define SIMMIPS_INSTR_HPP

#include <cstddef>
#include <cstdint>
#include <array>

#include "program.hpp"

enum reg_val {
    ZERO = 0, AT = 1,  V0 = 2,  V1 = 3,
    A0 = 4,   A1 = 5,  A2 = 6,  A3 = 7,
    T0 = 8,   T1 = 9,  T2 = 10, T3 = 11, 
    T4 = 12,  T5 = 13, T6 = 14, T7 = 15,
    S0 = 16,  S1 = 17, S2 = 18, S3 = 19, 
    S4 = 20,  S5 = 21, S6 = 22, S7 = 23,
    T8 = 24,  T9 = 25, K0 = 26, K1 = 27,
    GP = 28,  SP = 29, FP = 30, RA = 31,
    INVALID
};

enum arg_type {
    LABEL,
    REG,
    MEM,
    MEM_DIRECT,
    MEM_INDIRECT,
    IMMEDIATE,
    SOURCE,
    UNDEF
};

struct arg 
{
    enum arg_type type = UNDEF;
    std::ptrdiff_t offset;
    union {
        std::size_t label;
        enum reg_val reg;
        std::size_t mem;
        std::intmax_t imm;
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
    NEG_S,      NEG_U,
    AND,        NOR,          NOT,          OR,         XOR,
    JUMP,       BRANCH_EQ,    BRANCH_NE,
    BRANCH_LT,  BRANCH_LE,    BRANCH_GT,    BRANCH_GE,
    NOP,
    INVAL,    DIV_S_IND,    DIV_U_IND 
};

class instr
{
private:
    enum instr_type op = NOP;
    std::array<arg, 3> args;
public:
    instr();
    instr(enum instr_type type, arg a0, arg a1, arg a2);
    ~instr();
};

#endif /* SIMMIPS_INSTR_H */
