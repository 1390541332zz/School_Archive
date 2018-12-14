#ifndef ENVIRONMENT_FUNCTIONAL_H
#define ENVIRONMENT_FUNCTIONAL_H

#include "env_helper.hpp"
#include <cassert>

Expression apply_comb(std::vector<Expression> const & args)
{
    if (!nargs_equal(args, 2)) {
        throw SemanticError("Error: Incorrect number of arguments");
    }
    assert(args[0].scope != nullptr);
    auto & env = *(args[0].scope);
    if (!env.is_proc(args[0].head()) && !args[0].isLambda()) {
        throw SemanticError("Error: first argument to apply is not a procedure.");
    }
    if (!args[1].isList()) {
        throw SemanticError("Error: second argument to apply is not a list.");
    }
    if (env.is_proc(args[0].head()) && !args[0].isLambda()) {
        auto exp = Expression(args[1].tailConstBegin(), args[1].tailConstEnd());
        exp.head() = args[0].head();
        try {
            return exp.eval(env);
        } catch (SemanticError const & e) {
            std::string ex = "Error: during apply: " + std::string(e.what());
            throw SemanticError(ex);
        }
    }
    Environment lambda_env;
    auto lambda_expr = args[0];
    auto exp = *std::next(lambda_expr.tailConstBegin());
    auto val = args[1].tailConstBegin();
    lambda_env.parent = lambda_expr.scope;
    lambda_env.reset();
    for (auto arg = lambda_expr.tailConstBegin()->tailConstBegin();
         arg != lambda_expr.tailConstBegin()->tailConstEnd();
         ++arg, ++val) {
        lambda_env.add_exp(arg->head(), *val);
    }
    try {
        return exp.eval(lambda_env);
    } catch (SemanticError const & e) {
        std::string ex = "Error: during apply: " + std::string(e.what());
        throw SemanticError(ex);
    }
}
Expression map_comb(std::vector<Expression> const & args)
{
    if (!nargs_equal(args, 2)) {
        throw SemanticError("Error: Incorrect number of arguments");
    }
    assert(args[0].scope != nullptr);
    auto & env = *(args[0].scope);
    if (!env.is_proc(args[0].head()) && !args[0].isLambda()) {
        throw SemanticError("Error: first argument to map is not a procedure.");
    }
    if (!args[1].isList()) {
        throw SemanticError("Error: second argument to map is not a list.");
    }
    Expression result = Atom("list");
    for (auto val = args[1].tailConstBegin(); val != args[1].tailConstEnd(); ++val) {
        if (env.is_proc(args[0].head()) && !args[0].isLambda()) {
            Expression exp = args[0].head();
            exp.append(*val);
            try {
                result.append(exp.eval(env));
                continue;
            } catch (SemanticError const & e) {
                std::string ex = "Error: during map: " + std::string(e.what());
                throw SemanticError(ex);
            }
        }
        auto lambda_expr = args[0];
        auto exp = *std::next(lambda_expr.tailConstBegin());
        auto arg = args[0].tailConstBegin()->tailConstBegin();
        Environment lambda_env;
        lambda_env.parent = lambda_expr.scope;
        lambda_env.reset();
        lambda_env.add_exp(arg->head(), *val);
        try {
            result.append(exp.eval(lambda_env));
        } catch (SemanticError const & e) {
            std::string ex = "Error: during map: " + std::string(e.what());
            throw SemanticError(ex);
        }
    }
    return result;
}

#endif /* ENVIRONMENT_FUNCTIONAL_H */
