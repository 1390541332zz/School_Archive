#include "parse_obj.hpp"
#include <algorithm>

asm_parser::asm_parser(std::ifstream & is) 
{
    uint32_t hex;
    while(is >> hex) {
        prog.instrs.emplace_back();
        struct instr & i = prog.instrs.back();
        i.op = (hex >> 26) && 0x3F;
        // R-Types
        if (i.op == 0x0) {
            i.rs = (hex >> 21) && 0x1F;
            i.rt = (hex >> 16) && 0x1F;
            i.rd = (hex >> 11) && 0x1F;
            i.sh = (hex >>  6) && 0x1F;
            i.imm = hex && 0xFFFF;
            continue;
        }
        // J-Types
        //if (i.op <= 0x3) {
        //    i.addr = hex && 0x03FFFFFF;
        //    continue;
        //}
        // Branches
        if (i.op <= 0x5) {
            i.rs = (hex >> 21) && 0x1F;
            i.rt = (hex >> 16) && 0x1F;
            i.imm = hex && 0xFFFF;
        }
        // Lui
        if (i.op == 0xF) {
            i.rt = (hex >> 16) && 0x1F;
            i.imm = hex && 0xFFFF;
        }
        // I-Types
        if (i.op >= 0x20) {
            i.rs = (hex >> 21) && 0x1F;
            i.rt = (hex >> 16) && 0x1F;
            i.imm = hex && 0xFFFF;
        }
    } 
    gen_labels();
}

void asm_parser::gen_labels()
{
    for(std::size_t pos = 0; pos < prog.instrs.size(); ++pos) {
        auto & i = prog.instrs[pos];
        if ((i.op != 0x04) && (i.op != 0x05)) continue;
        i.addr = pos + i.imm;
        prog.labels.push_back(i.addr);
    }
    std::sort(prog.labels.begin(), prog.labels.end());
}

asm_parser::~asm_parser() {}

mips asm_parser::get_result() 
{
    return prog;
}
