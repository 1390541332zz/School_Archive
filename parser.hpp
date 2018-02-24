#ifndef SIMMIPS_PARSER_HPP
#define SIMMIPS_PARSER_HPP

#include <iostream>
#include <iterator>

#include "token.hpp"
#include "instr.hpp"
#include "program.hpp"

class program;

enum data_type {
   WORD = 4,
   HALF = 2,
   BYTE = 1,
   SPACE,
   ASCII,
   ASCIIZ,
   ERR 
};

class parser
{
private:
    program & prog;
    TokenList::const_iterator it;
    TokenList::const_iterator it_end;
    std::ostream & os;
    
    bool parse_data();
    bool parse_text();
    bool parse_constant();
    bool parse_label();
    bool parse_var();
    bool parse_ints(enum data_type type);
    bool parse_str(enum data_type type);
    bool parse_instr(); //TODO
    bool parse_sep(); //TODO
    bool parse_arg(arg & a, enum arg_type type); //TODO

    bool parse_tag(arg & a);
    bool parse_reg(arg & a);
    bool parse_mem(arg & a);
    bool parse_imm(arg & a);
    bool parse_source(arg & a);
public:
    parser(program & program, TokenList::const_iterator iter, 
           TokenList::const_iterator iter_end, std::ostream & log);
    ~parser();
    bool parse();
};

#endif /* SIMMIPS_PARSER_HPP  */
