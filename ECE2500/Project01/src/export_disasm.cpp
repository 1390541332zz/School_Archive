#include <iostream>
#include <iomanip>
#include <algorithm>
#include "export_disasm.hpp"

#define INSTRTAB 6 

#define OPTAB 7

#define A1TAB 7

#define A2TAB 12

#define LABELTAB 11


#define EXPORT_JR(OS, I, OP) do {                                             \
   os << std::setw(INSTRTAB)                                                  \
      << OP            << std::setw(OPTAB)                                    \
      << get_reg(I.rs) << std::endl;                                          \
} while (0);                                                                  

#define EXPORT_S(OS, I, OP) do {                                              \
   os << std::setw(INSTRTAB)                                                  \
      << OP            << std::endl;                                          \
} while (0);

#define EXPORT_SFT(OS, I, OP) do {                                            \
   os << std::setw(INSTRTAB)                                                  \
      << OP                   << std::setw(OPTAB)                             \
      << get_reg(I.rs) << ',' << std::setw(A1TAB)                             \
      << get_reg(I.rt) << ',' << std::setw(A2TAB)                             \
      << (std::uint16_t) I.sh << std::endl;                                   \
} while (0);

#define EXPORT_HL(OS, I, OP) do {                                             \
   os << std::setw(INSTRTAB)                                                  \
      << OP                   << std::setw(OPTAB)                             \
      << get_reg(I.rd)        << std::endl;                                   \
} while (0);

#define EXPORT_MD(OS, I, OP) do {                                             \
   os << std::setw(INSTRTAB)                                                  \
      << OP                   << std::setw(OPTAB)                             \
      << get_reg(I.rs) << ',' << std::setw(A1TAB)                             \
      << get_reg(I.rt)        << std::endl;                                   \
} while (0);

#define EXPORT_R(OS, I, OP) do {                                              \
   os << std::setw(INSTRTAB)                                                  \
      << OP                   << std::setw(OPTAB)                             \
      << get_reg(I.rd) << ',' << std::setw(A1TAB)                             \
      << get_reg(I.rs) << ',' << std::setw(A2TAB)                             \
      << get_reg(I.rt)        << std::endl;                                   \
} while (0);

#define EXPORT_I(OS, I, OP) do {                                              \
   os << std::setw(INSTRTAB)                                                  \
      << OP                   << std::setw(OPTAB)                             \
      << get_reg(I.rt) << ',' << std::setw(A1TAB)                             \
      << get_reg(I.rs) << ',' << std::setw(A2TAB)                             \
      << I.imm                << std::endl;                                   \
} while (0);

#define EXPORT_LI(OS, I, OP) do {                                             \
   os << std::setw(INSTRTAB)                                                  \
      << OP                   << std::setw(OPTAB)                             \
      << get_reg(I.rt) << ',' << std::setw(A1TAB)                             \
      << I.imm                << std::endl;                                   \
} while (0);

#define EXPORT_LS(OS, I, OP) do {                                             \
   os << std::setw(INSTRTAB)                                                  \
      << OP                                   << std::setw(OPTAB)             \
      << get_reg(I.rt) << ','                 << std::setw(A1TAB)             \
      << I.imm << '(' << get_reg(I.rs) << ')' << std::endl;                   \
} while (0);

#define EXPORT_B(OS, I, OP) do {                                              \
   os << std::setw(INSTRTAB)                                                  \
      << OP                    << std::setw(OPTAB)                            \
      << get_reg(I.rt) << ','  << std::setw(A1TAB)                            \
      << get_reg(I.rs) << ','  << std::setw(A2TAB)                            \
      << "Addr_" << I.imm * 4 << std::endl;                                  \
} while (0);

std::string get_reg(std::uint8_t r)
{
    switch (r) {
        case  0: return "$zero"; 
        case  1: return "$at";
        case  2: return "$v0";
        case  3: return "$v1";
        case  4: return "$a0";
        case  5: return "$a1";
        case  6: return "$a2";
        case  7: return "$a3";
        case  8: return "$t0";
        case  9: return "$t1";
        case 10: return "$t2";
        case 11: return "$t3";
        case 12: return "$t4";
        case 13: return "$t5";
        case 14: return "$t6";
        case 15: return "$t7";
        case 16: return "$s0";
        case 17: return "$s1";
        case 18: return "$s2";
        case 19: return "$s3";
        case 20: return "$s4";
        case 21: return "$s5";
        case 22: return "$s6";
        case 23: return "$s7";
        case 24: return "$t8";
        case 25: return "$t9";
        case 26: return "$k0";
        case 27: return "$k1";
        case 28: return "$gp";
        case 29: return "$sp";
        case 30: return "$fp";
        case 31: return "$ra";
        default: return "ERROR: Invalid Register";
    }
}

int asm_export(std::ostream & os, struct mips const & prog)
{
    for(std::size_t pos = 0; pos < prog.instrs.size(); ++pos) {
        auto const & i = prog.instrs[pos];
        auto res = std::find(prog.labels.begin(), prog.labels.end(), pos);
        if (res != prog.labels.end()) {
            os << std::setw(LABELTAB)
               << "Addr_" << pos * 4 << ':';
        }
        if (i.op == 0x0) switch (i.func) {
            case 0x00: EXPORT_SFT(os, i, "sll"  ); continue;  
            case 0x02: EXPORT_SFT(os, i, "srl"  ); continue;
            case 0x03: EXPORT_SFT(os, i, "sra"  ); continue;
            case 0x04: EXPORT_R(  os, i, "sllv" ); continue;
            case 0x06: EXPORT_R(  os, i, "srlv" ); continue;
            case 0x07: EXPORT_R(  os, i, "srav" ); continue;
            case 0x10: EXPORT_HL( os, i, "mfhi" ); continue;
            case 0x11: EXPORT_HL( os, i, "mthi" ); continue;
            case 0x12: EXPORT_HL( os, i, "mflo" ); continue;
            case 0x13: EXPORT_HL( os, i, "mtlo" ); continue;
            case 0x18: EXPORT_MD( os, i, "mult" ); continue;
            case 0x19: EXPORT_MD( os, i, "multu"); continue;
            case 0x1a: EXPORT_MD( os, i, "div"  ); continue;
            case 0x1b: EXPORT_MD( os, i, "divu" ); continue;
            case 0x20: EXPORT_R(  os, i, "add"  ); continue;
            case 0x21: EXPORT_R(  os, i, "addu" ); continue;
            case 0x22: EXPORT_R(  os, i, "sub"  ); continue;
            case 0x23: EXPORT_R(  os, i, "subu" ); continue;
            case 0x24: EXPORT_R(  os, i, "and"  ); continue;
            case 0x25: EXPORT_R(  os, i, "or"   ); continue;
            case 0x26: EXPORT_R(  os, i, "xor"  ); continue;
            case 0x27: EXPORT_R(  os, i, "nor"  ); continue;
            case 0x2a: EXPORT_R(  os, i, "slt"  ); continue;
            case 0x2b: EXPORT_R(  os, i, "sltu" ); continue;
                       
            case 0x08: EXPORT_JR( os, i, "jr"   ); continue;
            case 0x09: EXPORT_JR( os, i, "jalr" ); continue;
            
            case 0x0C: EXPORT_S( os, i, "syscall" ); continue;
            default: std::cerr << "Unknown Instruction"; return -1;
        }
        // J-Types
        //if (i.op <= 0x3) {
        //}
        // I-Types
        switch (i.op) {
            case 0x0F: EXPORT_LI( os, i, "lui" ); continue;
            
            case 0x04: EXPORT_B( os, i, "beq" ); continue;
            case 0x05: EXPORT_B( os, i, "bne" ); continue;
            
            case 0x08: EXPORT_I( os, i, "addi" ); continue;
            case 0x09: EXPORT_I( os, i, "addiu"); continue;
            case 0x0A: EXPORT_I( os, i, "slti" ); continue;
            case 0x0B: EXPORT_I( os, i, "sltiu"); continue;
            case 0x0C: EXPORT_I( os, i, "andi" ); continue;
            case 0x0D: EXPORT_I( os, i, "ori"  ); continue;
            case 0x0E: EXPORT_I( os, i, "xori" ); continue;
            
            case 0x20: EXPORT_LS( os, i, "lb" ); continue;
            case 0x21: EXPORT_LS( os, i, "lh" ); continue;
            case 0x22: EXPORT_LS( os, i, "lwl"); continue;
            case 0x23: EXPORT_LS( os, i, "lw" ); continue;
            case 0x24: EXPORT_LS( os, i, "lbu"); continue;
            case 0x25: EXPORT_LS( os, i, "lhu"); continue;
            case 0x26: EXPORT_LS( os, i, "lwr"); continue;
            case 0x28: EXPORT_LS( os, i, "sb" ); continue;
            case 0x29: EXPORT_LS( os, i, "sh" ); continue;
            case 0x2A: EXPORT_LS( os, i, "swl"); continue;
            case 0x2B: EXPORT_LS( os, i, "sw" ); continue;
            case 0x30: EXPORT_LS( os, i, "ll" ); continue;
            case 0x38: EXPORT_LS( os, i, "sc" ); continue;
            default: std::cerr << "Unknown Instruction"; return -1;
        }
    }
    return 0;
}
