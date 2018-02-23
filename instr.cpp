#include "instr.hpp"

instr::instr() {}

instr::instr(enum instr_type type, arg a0 = arg(), arg a1 = arg(), arg a2 = arg())
{
    op = type;
    arg[0] = a0;
    arg[1] = a1;
    arg[2] = a2;
}

instr::~instr() {}
