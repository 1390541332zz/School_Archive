#include <cstdlib>
#include <iostream>
#include <fstream>
#include "program.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2) return EXIT_FAILURE;
    std::string ifs(argv[1]);
    std::ifstream is(ifs);
    program prog(is, std::cerr);
    if(!prog.isValid()) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
