#include "plotscript_eval.hpp"

int main(int argc, char * argv[])
{
    if (argc == 2) {
        return eval_from_file(argv[1]);
    }
    if (argc == 3) {
        if (std::string(argv[1]) == "-e") {
            return eval_from_command(argv[2]);
        }
        error("Incorrect number of command line arguments.");
        return EXIT_FAILURE;
    }
    return repl();
}
