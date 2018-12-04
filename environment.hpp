/*! \file environment.hpp
This file defines the module representing the environment.

The environment is the collection of all previously defined procedures, e.g.
the built-in ones, and previously defined symbols. The environment is used
by the interpreter to store and lookup the value of symbols and procedures as
needed.
 */

#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <map>

#include "atom.hpp"
#include "expression.hpp"
#include "semantic_error.hpp"

/*! \typedef Procedure
\brief A Procedure is a C++ function pointer taking a vector of 
       Expressions as arguments and returning an Expression.
*/
using Procedure = Expression (*)(std::vector<Expression> const & args);

/*! \class Environment
\brief A class representing the interpreter environment.

An instance of Environment allows the interpreter to track previously defined
procedures and definitions, either built-in or defined during execution.

To lookup a symbol use one of the member functions is_exp or is_proc, or if you
do not care about
what the symbol maps to is_known. Depending on the value these member functions
return you can obtain
the mapped-to value using get_exp or get_proc.

To add an symbol to expression mapping use the add_exp member function.
 */
class Environment {
public:
    /*! Construct the default environment with built-in procedures and
   * definitions. */
    Environment() noexcept;

    ~Environment() = default;

    Environment(Environment const &) = delete;
    Environment & operator=(Environment const &) = delete;
    Environment(Environment &&) = delete;
    Environment & operator=(Environment &&) = delete;

    /*! Determine if a symbol is known to the environment.
    \param sym the sumbol to lookup
    \return true if the symbol has been defined in the environment
   */
    bool is_known(Atom const & sym) const noexcept;

    /*! Determine if a symbol has been defined as an expression.
    \param sym the sumbol to lookup
    \return true if the symbol has been defined in the environment as an
    expression
   */
    bool is_exp(Atom const & sym) const noexcept;

    /*! Get the Expression the argument symbol maps to.
    \param sym the symbol to lookup
    \return the expression the symbol maps to or an Expression of NoneType
  */
    Expression get_exp(Atom const & sym) const noexcept;

    /*! Add a mapping from sym argument to the exp argument within the environment.
    \param sym the symbol to add
    \param exp the expression the symbol should map to
   */
    void add_exp(Atom const & sym, Expression const & exp);

    /*! Determine if a symbol has been defined as a procedure
    \param sym the symbol to lookup
    \return true if thr symbol maps to a procedure
   */
    bool is_proc(Atom const & sym) const noexcept;

    /*! Get the Procedure the argument symbol maps to
    \param sym the symbol to lookup
    \return the procedure it maps to 

    Note: return the default procedure if argument is not a symbol
          or does not map to a known procedure.
  */
    Procedure get_proc(Atom const & sym) const noexcept;

    /*! Reset the environment to its default state. */
    void reset() noexcept;

    /*! parent scope environment */
    // Would use plain getters and setters anyways so might as well be public
    Environment const * parent = nullptr;

private:
    // Environment is a mapping from symbols to expressions or procedures
    enum EnvResultType { ExpressionType,
        ProcedureType };

    struct EnvResult {
        EnvResultType type = ExpressionType;
        Expression exp = Expression(); // used when type is ExpressionType
        Procedure proc = Procedure(); // used when type is ProcedureType

        // constructors for use in container emplace
        EnvResult() noexcept = default;
        EnvResult(EnvResultType t, Expression e) noexcept
            : type(t)
            , exp(std::move(e))
        {
        }
        EnvResult(EnvResultType t, Procedure p) noexcept
            : type(t)
            , proc(p)
        {
        }
    };
    // the environment map
    std::map<std::string, EnvResult> envmap;
};

#endif
