#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "interpreter.hpp"
#include "semantic_error.hpp"
#include "startup_config.hpp"

void prompt()
{
    std::cout << "\nplotscript> ";
}

std::string readline()
{
    std::string line;
    std::getline(std::cin, line);

    return line;
}

void error(std::string const & err_str)
{
    std::cerr << "Error: " << err_str << std::endl;
}

void info(std::string const & err_str)
{
    std::cout << "Info: " << err_str << std::endl;
}

int eval_from_stream(std::istream & stream)
{

    Interpreter interp;

    std::ifstream setupifs(STARTUP_FILE);
    if (!interp.parseStream(setupifs)) {
        error("Invalid Startup Program. Could not parse.");
        return EXIT_FAILURE;
    }
    try {
        Expression exp = interp.evaluate();
    } catch (SemanticError const & ex) {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    if (!interp.parseStream(stream)) {
        error("Invalid Program. Could not parse.");
        return EXIT_FAILURE;
    }
    try {
        Expression exp = interp.evaluate();
        std::cout << exp << std::endl;
    } catch (SemanticError const & ex) {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int eval_from_file(std::string const & filename)
{

    std::ifstream ifs(filename);

    if (!ifs) {
        error("Could not open file for reading.");
        return EXIT_FAILURE;
    }

    return eval_from_stream(ifs);
}

int eval_from_command(std::string const & argexp)
{

    std::istringstream expression(argexp);

    return eval_from_stream(expression);
}

// A REPL is a repeated read-eval-print loop
int repl()
{
    Interpreter interp;
    std::ifstream setupifs(STARTUP_FILE);
    if (!interp.parseStream(setupifs)) {
        error("Invalid Startup Program. Could not parse.");
        return EXIT_FAILURE;
    }
    try {
        Expression exp = interp.evaluate();
    } catch (SemanticError const & ex) {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    while (!std::cin.eof()) {

        prompt();
        std::string line = readline();

        if (line.empty()) {
            continue;
        }
        std::istringstream expression(line);

        if (!interp.parseStream(expression)) {
            error("Invalid Expression. Could not parse.");
            continue;
        }
        try {
            Expression exp = interp.evaluate();
            std::cout << exp << std::endl;
        } catch (SemanticError const & ex) {
            std::cerr << ex.what() << std::endl;
        }
    }
    return EXIT_SUCCESS;
}

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
