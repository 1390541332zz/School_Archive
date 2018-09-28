#ifndef ENVIRONMENT_FUNCTIONAL_H
#define ENVIRONMENT_FUNCTIONAL_H

#include "env_helper.hpp"

Expression lambda(const std::vector<Expression>& args)
{
    return Expression(args.cbegin(), args.cend());
}

Expression apply_comb(const std::vector<Expression>& args, Environment & env)
{
    if (!args[0].isFun() && !args[0].isLambda()) {
        throw SemanticError("Error: first argument to apply is not a procedure.");
    }
    if (!args[1].isList()) {
        throw SemanticError("Error: second argument to apply is not a list.");
    }
    if (args[0].isFun()) {
        auto exp = Expression(args[1].tailConstBegin(), args[1].tailConstEnd());
        exp.head() = args[0].head();
        return exp;
    }

    auto lambda_env = env;
    auto lambda_expr = args[0];
    auto exp = *std::next(lambda_expr.tailConstBegin());
    auto val = args[1].tailConstBegin();
    for (auto arg = lambda_expr.tailConstBegin()->tailConstBegin(); 
             arg != lambda_expr.tailConstBegin()->tailConstEnd();
         ++arg, ++val) 
    {
        lambda_env.add_exp_force(arg->head(), *val);
    }
    
    return exp.eval(lambda_env);
}

Expression map_comb(const std::vector<Expression>& args)
{
    return Expression(args.cbegin(), args.cend());
}

#endif /* ENVIRONMENT_FUNCTIONAL_H */
