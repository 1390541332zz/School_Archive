#ifndef LAMBDA_MIPS_OBJ_H
#define LAMBDA_MIPS_OBJ_H

#include <fstream>
#include "mips_asm.hpp"

class asm_parser {
private:
    struct mips prog;
    void gen_labels();    
public:
    asm_parser(std::ifstream & is);
    ~asm_parser();
    mips get_result();
};

#endif /* LAMBDA_MIPS_OBJ_H */
