#ifndef SIMMIPS_LEXER_HPP
#define SIMMIPS_LEXER_HPP

#include <istream>
#include <string>
#include <stack>
#include <limits>

#include "token.hpp"

/* Tokenize input text string into a list of tokens.
On error, the last token is of type ERROR and the value is the
error message.
 */
TokenList tokenize(std::istream & is);

#endif /* SIMMIPS_LEXER_HPP */
