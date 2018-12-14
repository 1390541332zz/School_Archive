#ifndef ENVIRONMENT_LIST_H
#define ENVIRONMENT_LIST_H

#include "env_helper.hpp"

Expression list(std::vector<Expression> const & args)
{
    return Expression(args.cbegin(), args.cend());
}

Expression first(std::vector<Expression> const & args)
{
    if (!nargs_equal(args, 1)) {
        throw SemanticError("Error: more than one argument in call to first.");
    }
    if (!args[0].isList()) {
        throw SemanticError("Error: argument to first is not a list.");
    }
    if (args[0].arg_length() == 0) {
        throw SemanticError("Error: argument to first is an empty list.");
    }
    return *(args[0].tailConstBegin());
}

Expression rest(std::vector<Expression> const & args)
{
    if (!nargs_equal(args, 1)) {
        throw SemanticError("Error: more than one argument in call to rest.");
    }
    if (!args[0].isList()) {
        throw SemanticError("Error: argument to rest is not a list.");
    }
    if (args[0].arg_length() == 0) {
        throw SemanticError("Error: argument to rest is an empty list.");
    }
    return Expression(std::next(args[0].tailConstBegin()), args[0].tailConstEnd());
}

Expression length(std::vector<Expression> const & args)
{
    if (!nargs_equal(args, 1)) {
        throw SemanticError("Error: more than one argument in call to length.");
    }
    if (!args[0].isList()) {
        throw SemanticError("Error: argument to length is not a list.");
    }
    return Expression(std::distance(args[0].tailConstBegin(), args[0].tailConstEnd()));
}

Expression append(std::vector<Expression> const & args)
{
    if (!nargs_equal(args, 2)) {
        throw SemanticError("Error: incorrect number of argument in call to append.");
    }
    if (!args[0].isList()) {
        throw SemanticError("Error: first argument to append is not a list.");
    }
    auto exp = Expression(args[0].tailConstBegin(), args[0].tailConstEnd());
    exp.append(args[1]);
    return exp;
}

Expression join(std::vector<Expression> const & args)
{
    if (!nargs_equal(args, 2)) {
        throw SemanticError("Error: incorrect number of argument in call to join.");
    }
    if (!args[0].isList() || !args[1].isList()) {
        throw SemanticError("Error: argument to join is not a list.");
    }
    auto exp = Expression(args[0].tailConstBegin(), args[0].tailConstEnd());
    for (auto it = args[1].tailConstBegin(); it < args[1].tailConstEnd(); ++it) {
        exp.append(*it);
    }
    return exp;
}

Expression range(std::vector<Expression> const & args)
{
    if (!nargs_equal(args, 3)) {
        throw SemanticError("Error: incorrect number of argument in call to join.");
    }
    if ((!args[0].isHeadNumber())
        || (!args[1].isHeadNumber())
        || (!args[2].isHeadNumber())) {
        throw SemanticError("Error: argument to range is not a number.");
    }
    auto lbound = args[0].head().asNumber();
    auto ubound = args[1].head().asNumber();
    auto rate = args[2].head().asNumber();

    if (lbound > ubound) {
        throw SemanticError("Error: begin greater than end in range.");
    }
    if (rate <= 0) {
        throw SemanticError("Error: negative or zero increment in range.");
    }
    std::string const s = "list";
    auto exp = Expression(s);
    for (auto i = lbound; i <= ubound; i += rate) {
        exp.append(Atom(i));
    }
    return exp;
}

#endif /* ENVIRONMENT_LIST_H */
