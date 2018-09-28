#ifndef ENVIRONMENT_HELPER_H
#define ENVIRONMENT_HELPER_H

#include "environment.hpp"

/*********************************************************************** 
Helper Functions
**********************************************************************/

// predicate, the number of args is nargs
bool nargs_equal(const std::vector<Expression>& args, unsigned nargs)
{
    return args.size() == nargs;
}

// the default procedure always returns an expresison of type None
Expression default_proc(const std::vector<Expression>& args)
{
    args.size(); // make compiler happy we used this parameter
    return Expression();
}

#endif /* ENVIRONMENT_HELPER_H */
