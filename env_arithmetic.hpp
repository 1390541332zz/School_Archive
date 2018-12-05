#ifndef ENVIRONMENT_ARITHMETIC_H
#define ENVIRONMENT_ARITHMETIC_H

#include "env_helper.hpp"
/*****************************************************************************
Math Helper Functions
*****************************************************************************/

bool anyargs_complex(std::vector<Expression> const & args)
{
    for (auto const & x : args) {
        if (x.isHeadComplex()) {
            return true;
        }
    }
    return false;
}

bool isComplex(std::complex<double> x)
{
    double absi = std::abs(x.imag());
    return (!std::isnan(absi)
        && (absi >= std::numeric_limits<float>::epsilon()));
}

//---------------------------------------------------------------------------//

Expression add(std::vector<Expression> const & args)
{
    // check all aruments are numbers, while adding
    std::complex<double> result(0, 0);
    for (auto & a : args) {
        result += a.head().asComplex();
    }
    if (anyargs_complex(args)) {
        return Expression(result);
    }
    return Expression(result.real());
}

Expression mul(std::vector<Expression> const & args)
{
    // check all aruments are numbers, while multiplying
    std::complex<double> result(1, 0);
    for (auto & a : args) {
        result *= a.head().asComplex();
    }

    if (anyargs_complex(args)) {
        return Expression(result);
    }
    return Expression(result.real());
}

Expression subneg(std::vector<Expression> const & args)
{
    std::complex<double> result(0, 0);

    // preconditions
    if (nargs_equal(args, 1)) {
        result = -args[0].head().asComplex();
    } else if (nargs_equal(args, 2)) {
        result = args[0].head().asComplex() - args[1].head().asComplex();
    } else {
        throw SemanticError("Error in call to subtraction or negation: invalid number of arguments.");
    }

    if (anyargs_complex(args)) {
        return Expression(result);
    }
    return Expression(result.real());
}

Expression div(std::vector<Expression> const & args)
{
    std::complex<double> result(0, 0);
    if (nargs_equal(args, 1)) {
        result = std::complex<double>(1, 0) / args[0].head().asComplex();
    } else if (nargs_equal(args, 2)) {
        result = args[0].head().asComplex() / args[1].head().asComplex();
    } else {
        throw SemanticError("Error in call to division: invalid number of arguments.");
    }
    if (anyargs_complex(args)) {
        return Expression(result);
    }
    return Expression(result.real());
}

Expression pow(std::vector<Expression> const & args)
{
    if (!nargs_equal(args, 2)) {
        throw SemanticError("Error in call to power: invalid number of arguments.");
    }
    auto result = std::pow(args[0].head().asComplex(), args[1].head().asComplex());
    if (anyargs_complex(args)) {
        return Expression(result);
    }
    return Expression(result.real());
}

Expression sqrt(std::vector<Expression> const & args)
{
    if (!nargs_equal(args, 1)) {
        throw SemanticError("Error in call to square root: invalid number of arguments.");
    }
    auto result = std::sqrt(args[0].head().asComplex());
    if (args[0].isHeadComplex() || isComplex(result)) {
        return Expression(result);
    }
    return Expression(result.real());
}

Expression natlog(std::vector<Expression> const & args)
{
    if (!nargs_equal(args, 1)) {
        throw SemanticError("Error in call to natural log: invalid number of arguments.");
    }
    if (std::abs(args[0].head().asComplex()) == 0) {
        throw SemanticError("Error in call to natural log: invalid argument.");
    }
    auto result = std::log(args[0].head().asComplex());
    if (args[0].isHeadComplex() || isComplex(result)) {
        return Expression(result);
    }
    return Expression(result.real());
}

Expression sin(std::vector<Expression> const & args)
{
    if (!nargs_equal(args, 1)) {
        throw SemanticError("Error in call to sin: invalid number of arguments.");
    }
    auto result = std::sin(args[0].head().asComplex());
    return Expression(result.real());
}

Expression cos(std::vector<Expression> const & args)
{
    if (!nargs_equal(args, 1)) {
        throw SemanticError("Error in call to cos: invalid number of arguments.");
    }
    auto result = std::cos(args[0].head().asComplex());
    if (args[0].isHeadComplex()) {
        return Expression(result);
    }
    return Expression(result.real());
}

Expression tan(std::vector<Expression> const & args)
{
    if (!nargs_equal(args, 1)) {
        throw SemanticError("Error in call to tan: invalid number of arguments.");
    }
    auto result = std::tan(args[0].head().asComplex());
    return Expression(result.real());
}

Expression real(std::vector<Expression> const & args)
{
    if (!nargs_equal(args, 1)) {
        throw SemanticError("Error in call to real: invalid number of arguments.");
    }
    if (!(args[0].isHeadComplex())) {
        throw SemanticError("Error in call to real: non-complex argument.");
    }

    auto result = std::real(args[0].head().asComplex());
    return Expression(result);
}

Expression imag(std::vector<Expression> const & args)
{
    if (!nargs_equal(args, 1)) {
        throw SemanticError("Error in call to imag: invalid number of arguments.");
    }
    if (!(args[0].isHeadComplex())) {
        throw SemanticError("Error in call to imag: non-complex argument.");
    }

    auto result = std::imag(args[0].head().asComplex());
    return Expression(result);
}

Expression mag(std::vector<Expression> const & args)
{
    if (!nargs_equal(args, 1)) {
        throw SemanticError("Error in call to mag: invalid number of arguments.");
    }
    if (!(args[0].isHeadComplex())) {
        throw SemanticError("Error in call to mag: non-complex argument.");
    }

    auto result = std::abs(args[0].head().asComplex());
    return Expression(result);
}

Expression arg(std::vector<Expression> const & args)
{
    if (!nargs_equal(args, 1)) {
        throw SemanticError("Error in call to arg: invalid number of arguments.");
    }
    if (!(args[0].isHeadComplex())) {
        throw SemanticError("Error in call to arg: non-complex argument.");
    }

    auto result = std::arg(args[0].head().asComplex());
    return Expression(result);
}

Expression conj(std::vector<Expression> const & args)
{
    if (!nargs_equal(args, 1)) {
        throw SemanticError("Error in call to conj: invalid number of arguments.");
    }
    if (!(args[0].isHeadComplex())) {
        throw SemanticError("Error in call to conj: non-complex argument.");
    }

    auto result = std::conj(args[0].head().asComplex());
    return Expression(result);
}

#endif /* ENVIRONMENT_ARITHMETIC_H */
