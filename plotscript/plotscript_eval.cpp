#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "interpreter.hpp"
#include "plotscript_eval.hpp"
#include "semantic_error.hpp"
#include "startup_config.hpp"
#include "message_queue.hpp"

//message_queue<std::string> & access_interpthread(enum thread_command cmd)
//{
//    static std::thread interp;
//    static bool halt = false;
//    auto f = [&q, &halt] () {
//        while(!halt) {
//            
//        }
//    };
//    static message_queue<std::string> q;
//    switch (cmd) {
//        case START_T:
//            halt = false;
//            interp = std::thread(f);
//            break;
//        case STOP_T:
//            halt = true;
//            f.join();
//            break;
//        case RESET_T:
//            halt = true;
//            f.join();
//            halt = false;
//            interp = std::thread(f);
//            break;
//        default:
//            break;
//    };
//    return q;
//}

void prompt(std::ostream & os = DEFAULT_COUT)
{
    os << "\nplotscript> ";
}

std::string readline(std::istream & is = DEFAULT_CIN)
{
    std::string line;
    std::getline(is, line);

    return line;
}

void error(std::string const & err_str, std::ostream & es)
{
    es << "Error: " << err_str << std::endl;
}

void info(std::string const & err_str, std::ostream & os = DEFAULT_COUT)
{
    os << "Info: " << err_str << std::endl;
}

int eval_from_stream(std::istream & is, std::ostream & os, std::ostream & es)
{
    Expression e{};
    return eval_from_stream_e(e, is, os, es);
}

int eval_from_stream_e(Expression & e_out, std::istream & is,
    std::ostream & os, std::ostream & es)
{

    Interpreter interp;
    std::ifstream setupifs(STARTUP_FILE);
    if (!interp.parseStream(setupifs)) {
        error("Invalid Startup Program. Could not parse.");
        return EXIT_FAILURE;
    }
    try {
        e_out = interp.evaluate();
    } catch (SemanticError const & ex) {
        es << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    if (!interp.parseStream(is)) {
        error("Invalid Program. Could not parse.", es);
        return EXIT_FAILURE;
    }
    try {
        e_out = interp.evaluate();
        os << e_out << std::endl;
    } catch (SemanticError const & ex) {
        es << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int eval_from_file(std::string const & filename, std::ostream & os, std::ostream & es)
{
    std::ifstream ifs(filename);

    if (!ifs) {
        error("Could not open file for reading.", es);
        return EXIT_FAILURE;
    }

    return eval_from_stream(ifs, os, es);
}

int eval_from_command(std::string const & argexp, std::ostream & os, std::ostream & es)
{

    std::istringstream expression(argexp);

    return eval_from_stream(expression, os, es);
}

// A REPL is a repeated read-eval-print loop
int repl(std::istream & is, std::ostream & os, std::ostream & es)
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
        es << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    while (!is.eof()) {

        prompt(os);
        std::string line = readline(is);

        if (line.empty()) {
            continue;
        }
        std::istringstream expression(line);

        if (!interp.parseStream(expression)) {
            error("Error: Invalid Expression. Could not parse.", es);
            continue;
        }
        try {
            Expression exp = interp.evaluate();
            os << exp << std::endl;
        } catch (SemanticError const & ex) {
            es << ex.what() << std::endl;
        }
    }
    return EXIT_SUCCESS;
}

//Expression eval_fn(Expression const & fn, std::vector<qreal> const & args)
//{
//    Environment e;
//    e.parent = fn.scope;
//    std::stringstream is;
//    is << "(map EVAL_FN_PLOTSCRIPT (list";
//    for (auto i : args) {
//        is << ' ' << i;
//    }
//    is << " ))";
//    
//    e.add_exp(Atom("EVAL_FN_PLOTSCRIPT"), fn);
//    Interpreter in {e};
//    in.parseStream(is);
//    return in.eval();
//}
