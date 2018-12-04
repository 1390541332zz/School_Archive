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

Environment::Environment() noexcept
{
    reset();
}

// Reset the environment to the default state.
void Environment::reset() noexcept
{
    static double const PI = std::atan2(0, -1);
    static double const EXP = std::exp(1);
    static std::complex<double> const IMAG = { 0, 1 };
    static std::vector<std::tuple<std::string, Procedure>> const procedures
        = {
              // clang-format off
              // operator,       procedure
              // - list operators - 
              { "list",          list           },
              { "first",         first          },
              { "rest",          rest           },
              { "length",        length         },
              { "append",        append         },
              { "join",          join           },
              { "range",         range          },
              // - functional operators - 
              { "apply",         apply_comb     },
              { "map",           map_comb       },
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

    if (parent != nullptr) {
        return;
    }
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

bool Environment::is_known(Atom const& sym) const noexcept
{
    if (!sym.isSymbol()) {
        return false;
    }
    auto result = envmap.find(sym.asSymbol());
    return (  (result != envmap.end())
           || (  (parent != nullptr) 
              && (result == envmap.end()) 
              && parent->is_known(sym)
              )
           );
}

bool Environment::is_exp(Atom const& sym) const noexcept
{
    if (!sym.isSymbol()) {
        return false;
    }
    auto result = envmap.find(sym.asSymbol());
    return (  (  (result != envmap.end()) 
              && (  (result->second.type == ExpressionType) 
                 || (sym.asSymbol() == "list") 
                 )
              )
           || (  (parent != nullptr) 
              && (result == envmap.end()) 
              && parent->is_exp(sym)
              )
           );
}

Expression Environment::get_exp(Atom const& sym) const noexcept
{
    if (!sym.isSymbol()) {
        return Expression();
    }
    auto result = envmap.find(sym.asSymbol());
    if ((result != envmap.end()) && (result->second.type == ExpressionType)) {
        return result->second.exp;
    }
    if ((parent != nullptr) && (result == envmap.end())) {
        return parent->get_exp(sym);
    }
    return Expression();
}

void Environment::add_exp(Atom const& sym, Expression const& exp)
{
    static Environment const default_env;
    
    if (!sym.isSymbol()) {
        throw SemanticError("Attempt to add non-symbol to environment");
    }
    if (default_env.is_known(sym)) {
        throw SemanticError("Attempt to override default symbol");
    }
    auto it = envmap.find(sym.asSymbol());
    if (it != envmap.end()) {
        envmap.erase(it);
    }

    envmap.emplace(sym.asSymbol(), EnvResult(ExpressionType, exp));
}

bool Environment::is_proc(Atom const& sym) const noexcept
{
    if (!sym.isSymbol()) {
        return false;
    }
    auto result = envmap.find(sym.asSymbol());
    return (  (  (result != envmap.end()) 
              && (result->second.type == ProcedureType)
              )
           || (  (parent != nullptr) 
              && (result == envmap.end()) 
              && parent->is_proc(sym)
              )
           );
}

Procedure Environment::get_proc(Atom const& sym) const noexcept
{
    if (!sym.isSymbol()) {
        return default_proc;
    }
    auto result = envmap.find(sym.asSymbol());
    if ((result != envmap.end()) && (result->second.type == ProcedureType)) {
        return result->second.proc;
    }
    if ((parent != nullptr) && (result == envmap.end())) {
        return parent->get_proc(sym);
    }

    return default_proc;
}
