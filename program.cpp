#include "program.hpp"

program::program(std::istream & is, std::ostream & os = std::cout) 
{
    parser parser;
   
    TokenList toklist = tokenize(is);
    parser.parse(*this, toklist.cbegin(), toklist.cend(), os);
}

program::~program() {}
