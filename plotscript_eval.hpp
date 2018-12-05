#ifndef PLOTSCRIPT_EVAL_H
#define PLOTSCRIPT_EVAL_H

#include "expression.hpp"
#include <iostream>

#define DEFAULT_COUT std::cout
#define DEFAULT_CERR std::cerr
#define DEFAULT_CIN std::cin

void error(std::string const & err_str, std::ostream & es = DEFAULT_CERR);

int eval_from_stream(std::istream & is = DEFAULT_CIN,
    std::ostream & os = DEFAULT_COUT,
    std::ostream & es = DEFAULT_CERR);

int eval_from_stream_e(Expression & e_out,
    std::istream & is = DEFAULT_CIN,
    std::ostream & os = DEFAULT_COUT,
    std::ostream & es = DEFAULT_CERR);

int eval_from_file(std::string const & filename,
    std::ostream & os = DEFAULT_COUT,
    std::ostream & es = DEFAULT_CERR);

int eval_from_command(std::string const & argexp,
    std::ostream & os = DEFAULT_COUT,
    std::ostream & es = DEFAULT_CERR);

// A REPL is a repeated read-eval-print loop
int repl(std::istream & is = DEFAULT_CIN,
    std::ostream & os = DEFAULT_COUT,
    std::ostream & es = DEFAULT_CERR);

#endif /* PLOTSCRIPT_EVAL_H */
