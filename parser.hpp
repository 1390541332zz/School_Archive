#ifndef SIMMIPS_PARSER_HPP
#define SIMMIPS_PARSER_HPP

#include <iostream>
#include <iterator>
#include <cmath>

#include "program.hpp"
#include "instr.hpp"
#include "token.hpp"

class program;
struct arg;
class instr;
enum arg_type : std::uint8_t;


enum data_type {
   WORD = 4,
   HALF = 2,
   BYTE = 1,
   SPACE = 3,
   ASCII = 5,
   ASCIIZ = 6,
   ERR = 7
};

class parser
{
private:
    program & prog;
    TokenList::const_iterator it;
    TokenList::const_iterator it_end;
    std::ostream & os = std::cout;
    
public:
    bool parse_data();
    bool parse_text();
    bool parse_constant();
    bool parse_label();
    bool parse_var();
    bool parse_ints(enum data_type type);
    bool parse_str(enum data_type type);
    bool parse_instr();
    bool parse_sep(); 
    bool parse_arg(arg & a, enum arg_type type);

    bool parse_tag(arg & a);
    bool parse_reg(arg & a);
    bool parse_mem(arg & a);
    bool parse_imm(arg & a);
    bool parse_source(arg & a);

    parser(program & program, TokenList::const_iterator iter, 
           TokenList::const_iterator iter_end, std::ostream & log);
    ~parser();
    bool parse();
};

#endif /* SIMMIPS_PARSER_HPP  */
