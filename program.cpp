#include "program.hpp"

program::program() {}

program::program(std::istream & is, std::ostream & log = std::cout) : os(log) 
{
    init(is);
}

program::~program() {}

bool program::init(std::istream & is)
{
    parser parser;
   
    TokenList toklist = tokenize(is);
    valid = parser.parse(*this, toklist.cbegin(), toklist.cend(), os);

    return valid;
}

bool program::isValid()
{
   return valid; 
}
