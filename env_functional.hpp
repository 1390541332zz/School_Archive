#ifndef ENVIRONMENT_FUNCTIONAL_H
#define ENVIRONMENT_FUNCTIONAL_H

#include "env_helper.hpp"

Expression lambda(const std::vector<Expression>& args)
{
    return Expression(args.cbegin(), args.cend());
}


#endif /* ENVIRONMENT_FUNCTIONAL_H */
