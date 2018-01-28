#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <vector>
#include <iterator>

//Operator Address Type
enum addr_type {
    IMMEDIATE,
    DIRECT,
    INDIRECT,
    UNDEF
};

//Instruction Arguments
struct arg {
    std::string arg = "";
    enum addr_type addr_type = UNDEF;
};

//Parsed Instructions
class instruction {
private:    
    std::string opcode;
    std::vector<arg> arguments;

    //Instruction Position (IAR/PC)
    std::size_t instr_addr = 0;

public:
    instruction();
    instruction(std::string const& op, std::forward_iterator<arg> first, 
            std::forward_iterator<arg> last);

    ~instruction();

    //Access Operator
    std::string& op();
    std::string const& op() const;

    //Access Arguments
    std::vector<arg>& args();
    std::vector<arg> const& args() const;
};

#endif /* INSTRUCTION_H */
