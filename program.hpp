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

class program
{
private:
    std::array<std::uint32_t, 32> reg = {0};
    std::vector<std::uint8_t> mem = {0};
    std::vector<instr> ops = {};
    std::map<std::string, std::size_t> label = {};
    std::map<std::string, std::intmax_t> constant = {};

    bool valid = false;

    std::ostream & os = std::cout;

    friend class parser;
public:
    program();
    program(std::istream & is, std::ostream & log);
    ~program();
    bool init(std::istream & is);
    bool isValid();
};

#endif /* SIMMIPS_PROGRAM_H */
