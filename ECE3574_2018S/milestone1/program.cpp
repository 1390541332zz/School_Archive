#include "program.hpp"

program::program() {}

program::program(std::istream & is, std::ostream & log = std::cout) : os(log) 
{
    init(is);
}

program::~program() {}

bool program::init(std::istream & is)
{
    TokenList toklist = tokenize(is);
    parser parser(*this, toklist.cbegin(), toklist.cend(), os); 
    valid = parser.parse();
    return valid;
}

bool program::isValid()
{
   return valid; 
}
