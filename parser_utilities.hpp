#ifndef SIMMIPS_PARSER_UTILITIES_H
#define SIMMIPS_PARSER_UTILITIES_H

#include "parser.hpp"

struct num {
    bool sign = false;
    std::intmax_t x = 0;
};

static std::string const digit = "0123456789";

// is_num(): Determines if the string is a valid integer.
static bool is_num(std::string const & str)
{
    return (  (!str.empty())
           && (str.find_first_not_of(digit + "+-") == std::string::npos)
           && (str.substr(1).find_first_not_of(digit) == std::string::npos));
}

// conv_data_type(): Converts a string into a data enum.
static enum data_type conv_data_type(std::string const & str) 
{
    if (str == ".word")   return WORD;
    if (str == ".half")   return HALF;
    if (str == ".byte")   return BYTE;
    if (str == ".space")  return SPACE;
    if (str == ".ascii")  return ASCII;
    if (str == ".asciiz") return ASCIIZ;
    return ERR;
}


// conv_reg_val(): Converts a string into a register value.
static enum reg_val conv_reg_val(std::string const & str) 
{
    if ((str ==  "$0") || (str == "$zero")) return ZERO;
    if ((str ==  "$1") || (str == "$at"))   return AT;
    
    if ((str ==  "$2") || (str == "$v0"))   return V0;
    if ((str ==  "$3") || (str == "$v1"))   return V1;
    
    if ((str ==  "$4") || (str == "$a0"))   return A0;
    if ((str ==  "$5") || (str == "$a1"))   return A1;
    if ((str ==  "$6") || (str == "$a2"))   return A2;
    if ((str ==  "$7") || (str == "$a3"))   return A3;
    
    if ((str ==  "$8") || (str == "$t0"))   return T0;
    if ((str ==  "$9") || (str == "$t1"))   return T1;
    if ((str == "$10") || (str == "$t2"))   return T2;
    if ((str == "$11") || (str == "$t3"))   return T3;
    if ((str == "$12") || (str == "$t4"))   return T4;
    if ((str == "$13") || (str == "$t5"))   return T5;
    if ((str == "$14") || (str == "$t6"))   return T6;
    if ((str == "$15") || (str == "$t7"))   return T7;
    
    if ((str == "$16") || (str == "$s0"))   return S0;
    if ((str == "$17") || (str == "$s1"))   return S1;
    if ((str == "$18") || (str == "$s2"))   return S2;
    if ((str == "$19") || (str == "$s3"))   return S3;
    if ((str == "$20") || (str == "$s4"))   return S4;
    if ((str == "$21") || (str == "$s5"))   return S5;
    if ((str == "$22") || (str == "$s6"))   return S6;
    if ((str == "$23") || (str == "$s7"))   return S7;

    if ((str == "$24") || (str == "$t8"))   return T8;
    if ((str == "$25") || (str == "$t9"))   return T9;

    if ((str == "$26") || (str == "$k0"))   return K0;
    if ((str == "$27") || (str == "$k1"))   return K1;

    if ((str == "$28") || (str == "$gp"))   return GP;
    if ((str == "$29") || (str == "$sp"))   return SP;
    if ((str == "$30") || (str == "$fp"))   return FP;
    if ((str == "$31") || (str == "$ra"))   return RA;
    return INVALID;
}

// conv_instr_type(): Converts a string into a instruction enum.
//     Note: div and divu have 2 forms that cannot be differentiated between 
//           and therefore is provided and indeterminate form until the 
//           number of arguments is deduced.
static enum instr_type conv_instr_type(std::string const & str) 
{
    if (str == "lw")    return LOAD_WORD;
    if (str == "lh")    return LOAD_HALF;
    if (str == "lb")    return LOAD_BYTE;
    if (str == "li")    return LOAD_IMM;
    if (str == "la")    return LOAD_ADD;

    if (str == "sw")    return STORE_WORD;
    if (str == "sh")    return STORE_HALF;
    if (str == "sb")    return STORE_BYTE;
    
    if (str == "move")  return MOVE;
    if (str == "mfhi")  return MOVE_FROM_HI;
    if (str == "mflo")  return MOVE_FROM_LO;
    if (str == "mthi")  return MOVE_TO_HI;
    if (str == "mtlo")  return MOVE_TO_LO;

    if (str == "add")   return ADD_S;
    if (str == "addu")  return ADD_U;
    
    if (str == "sub")   return SUB_S;
    if (str == "subu")  return SUB_U;
    
    if (str == "mul")   return MUL;
    if (str == "mulo")  return MUL_LO;
    if (str == "mulou") return MUL_LOU;
    if (str == "mult")  return MULT_S;
    if (str == "multu") return MULT_U;
    
    if (str == "div")   return DIV_S_IND;
    if (str == "divu")  return DIV_U_IND;

    if (str == "rem")   return REM_S;
    if (str == "remu")  return REM_U;
   
    if (str == "abs")   return ABS;

    if (str == "neg")   return NEG_S;
    if (str == "negu")  return NEG_U;
    
    if (str == "and")   return AND;
    if (str == "nor")   return NOR;
    if (str == "not")   return NOT;
    if (str == "or")    return OR;
    if (str == "xor")   return XOR;

    if (str == "j")     return JUMP;
    
    if (str == "beq")   return BRANCH_EQ;
    if (str == "bne")   return BRANCH_NE;
    if (str == "blt")   return BRANCH_LT;
    if (str == "ble")   return BRANCH_LE;
    if (str == "bgt")   return BRANCH_GT;
    if (str == "bge")   return BRANCH_GE;

    return INVAL;
}

// validate_int(): Bounds checks integer values. 
static bool validate_int(num i, enum data_type type)
{
    std::size_t sz = type*8;
    if ((type != WORD) && (type != HALF) && (type != BYTE)) {
            //TODO: ERROR This can't happen. Something is broken in the parser.
            return false;
    }
    if (  (i.x >= std::exp2(sz))
       || ((i.sign) && (i.x >= std::exp2(sz - 1)) && (i.x < std::exp2(sz - 1)))) {
        //TODO: ERROR Object value is out of bounds.
        return false;
    }
    return true;
}

#endif /* SIMMIPS_PARSER_UTILITIES_H */
