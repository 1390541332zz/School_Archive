#ifndef LAMBDA_MIPS_ASM_H
#define LAMBDA_MIPS_ASM_H

#include <ostream>
#include "mips_asm.hpp"

int asm_export(std::ostream & os, struct mips const & prog);

#endif /* LAMBDA_MIPS_ASM_H */
