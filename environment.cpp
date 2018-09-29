#include <cassert>
#include <cmath>
#include <complex>
#include <iterator>
#include <limits>
#include <tuple>

#include "environment.hpp"

// Static Class Files
#include "env_arithmetic.hpp"
#include "env_functional.hpp"
#include "env_helper.hpp"
#include "env_list.hpp"

Environment::Environment()
{
    reset();
}

// Reset the environment to the default state.
void Environment::reset()
{
    static std::vector<std::tuple<std::string, Procedure>> const procedures
        = {
              // clang-format off
              // operator,       procedure
              // - list operators - 
              { LIST_KEYWORD,    list           },
              { "first",         first          },
              { "rest",          rest           },
              { "length",        length         },
              { "append",        append         },
              { "join",          join           },
              { "range",         range          },
              // - functional operators - 
              { LAMBDA_KEYWORD,  lambda         },
              // - arithmetic operators - 
              { "+",             add            },
              { "-",             subneg         },
              { "*",             mul            },
              { "/",             div            },
              { "^",             pow            },
              { "sqrt",          sqrt           },
              { "ln",            natlog         },
              { "sin",           sin            },
              { "cos",           cos            },
              { "tan",           tan            },
              { "real",          real           },
              { "imag",          imag           },
              { "mag",           mag            },
              { "arg",           arg            },
              { "conj",          conj           },
              //clang-format on
          };

    envmap.clear();

    // Built-In value of pi
    envmap.emplace("pi", EnvResult(ExpressionType, Expression(PI)));

    // Built-In value of exp
    envmap.emplace("e", EnvResult(ExpressionType, Expression(EXP)));

    // Built-In value of imaginary i
    envmap.emplace("I", EnvResult(ExpressionType, Expression(IMAG)));

    for (auto& x : procedures) {
        envmap.emplace(std::get<0>(x), EnvResult(ProcedureType, std::get<1>(x)));
    }
}

bool Environment::is_known(const Atom& sym) const
{
    if (!sym.isSymbol())
        return false;

    return envmap.find(sym.asSymbol()) != envmap.end();
}

bool Environment::is_exp(const Atom& sym) const
{
    if (!sym.isSymbol())
        return false;

    auto result = envmap.find(sym.asSymbol());
    return (  (result != envmap.end()) 
           && (  (result->second.type == ExpressionType) 
              || (sym.asSymbol() == LIST_KEYWORD)
              )
           );
}

Expression Environment::get_exp(const Atom& sym) const
{
    Expression exp;

    if (sym.isSymbol()) {
        auto result = envmap.find(sym.asSymbol());
        if ((result != envmap.end()) && (result->second.type == ExpressionType)) {
            exp = result->second.exp;
        }
    }

    return exp;
}

void Environment::add_exp_force(const Atom& sym, const Expression& exp)
{

    if (!sym.isSymbol()) {
        throw SemanticError("Attempt to add non-symbol to environment");
    }

    auto it = envmap.find(sym.asSymbol());
    if (it != envmap.end()) {
        envmap.erase(it);
    }

    envmap.emplace(sym.asSymbol(), EnvResult(ExpressionType, exp));
}

void Environment::add_exp(const Atom& sym, const Expression& exp)
{

    if (!sym.isSymbol()) {
        throw SemanticError("Attempt to add non-symbol to environment");
    }

    // error if overwriting symbol map
    if (envmap.find(sym.asSymbol()) != envmap.end()) {
        throw SemanticError("Attempt to overwrite symbol in environemnt");
    }

    envmap.emplace(sym.asSymbol(), EnvResult(ExpressionType, exp));
}

bool Environment::is_proc(const Atom& sym) const
{
    if (!sym.isSymbol())
        return false;

    auto result = envmap.find(sym.asSymbol());
    return (result != envmap.end()) && (result->second.type == ProcedureType);
}

Procedure Environment::get_proc(const Atom& sym) const
{

    //Procedure proc = default_proc;

    if (sym.isSymbol()) {
        auto result = envmap.find(sym.asSymbol());
        if ((result != envmap.end()) && (result->second.type == ProcedureType)) {
            return result->second.proc;
        }
    }

    return default_proc;
}
