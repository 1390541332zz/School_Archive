#ifndef INSTRUCTION_H
#define INSTRUCTION_H

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
    addr_type addr_type = UNDEF;
};

//Parsed Instructions
class instruction {
private:    
    std::string op;
    std::vector<arg> args;

    //Instruction Position (IAR/PC)
    std::size_t instr_addr = 0;

public:
    instruction();
    instruction(std::string const& op, std::forward_iterator<arg> first, 
            std::forward_iterator<arg> last);

    ~instruction();

    //Access Operator
    std::string& op();
    std::string const& op();

    //Access Arguments
    std::vector<arg>& args() const;
    std::vector<arg> const& args() const;
};

#endif /* INSTRUCTION_H */
