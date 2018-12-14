#include "instr.hpp"

instr::instr() {}

instr::instr(enum instr_type type, arg a0 = arg(), arg a1 = arg(), arg a2 = arg())
{
    op = type;
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
}

instr::~instr() {}
