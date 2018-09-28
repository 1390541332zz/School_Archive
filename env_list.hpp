#ifndef ENVIRONMENT_LIST_H
#define ENVIRONMENT_LIST_H

#include "env_helper.hpp"

Expression list(const std::vector<Expression>& args)
{
    return Expression(args.cbegin(), args.cend());
}

#endif /* ENVIRONMENT_LIST_H */
