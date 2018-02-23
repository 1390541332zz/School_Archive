#ifndef SIMMIPS_PROGRAM_HPP
#define SIMMIPS_PROGRAM_HPP

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <map>

#include "lexer.hpp"
#include "parser.hpp"
#include "instr.hpp"

struct constant 
{
    bool sign = false;
    union {
        signed;
        unsigned;
    };
}

class program
{
private:
    std::array<std::uint32_t, 32> reg = {0};
    std::vector<std::uint8_t> mem = {0};
    std::vector<instr> instr = {};
    std::map<std::string, std::size_t> label = {};
    std::map<std::string, constant> constant = {};

    std::uint32_t & zero = reg[0];
    std::uint32_t & at   = reg[1];
    std::uint32_t & gp   = reg[28];
    std::uint32_t & sp   = reg[29];
    std::uint32_t & fp   = reg[30];
    std::uint32_t & ra   = reg[31];

    friend class parser;
public:
    program(std::istream & is; std::ostream & os);
    ~program();
}

#endif /* SIMMIPS_PROGRAM_H */
