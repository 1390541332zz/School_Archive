#include "lexer.hpp"

static std::string const err_mismatchParen = "ERROR: Mismatched Parenthesis on line ";
static std::string const err_mismatchQuote = "ERROR: Mismatched Quotation mark on line ";

static std::string const delimeter_chars = "#()\",=";

#define SYNTAX_CHECK(TOKLIST, TOKSTACK, CURLINE) do {                                                                  \
    if (!TOKSTACK.empty() && (TOKSTACK.top().type() == STRING_DELIM)) {                                                \
        TOKLIST.emplace_back(ERROR, CURLINE, err_mismatchQuote + std::to_string(CURLINE));                             \
        return TOKLIST;                                                                                                \
    } else if (!TOKSTACK.empty()) {                                                                                    \
        TOKLIST.emplace_back(ERROR, CURLINE, err_mismatchParen + std::to_string(CURLINE));                             \
        return TOKLIST;                                                                                                \
    }                                                                                                                  \
} while (0);

TokenList tokenize(std::istream & is)
{
    TokenList toklist;
    std::stack<Token> tokstack;
    char c;
    std::size_t curline = 1;

    while(is.get(c)) {
        std::string str;
        std::size_t delimeter_offset = std::string::npos;
        switch(c) {
            case '#':
                SYNTAX_CHECK(toklist, tokstack, curline);
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                ++curline;
                break;
            case '=':
                toklist.emplace_back(EQUAL, curline);
                break;
            case ',':
                toklist.emplace_back(SEP, curline);
            case '(':
                SYNTAX_CHECK(toklist, tokstack, curline);
                tokstack.emplace(OPEN_PAREN, curline);
                toklist.emplace_back(OPEN_PAREN, curline);
                break;
            case ')':
                if (tokstack.empty()) {
                    toklist.emplace_back(ERROR, curline, err_mismatchParen + std::to_string(curline));
                    return toklist;
                }
                tokstack.pop();
                toklist.emplace_back(CLOSE_PAREN, curline);
                break;
            case '\"':
                if (!tokstack.empty() && (tokstack.top().type() != STRING_DELIM)) {
                    //Panic
                } else if (!tokstack.empty() && (tokstack.top().line() != curline)) {
                    toklist.emplace_back(ERROR, curline, err_mismatchQuote + std::to_string(curline));
                    return toklist;
                } else if (!tokstack.empty()) {
                    tokstack.pop();
                } else {
                    tokstack.emplace(STRING_DELIM, curline);
                }
                toklist.emplace_back(STRING_DELIM, curline);
                break;
            case '\n':
                SYNTAX_CHECK(toklist, tokstack, curline);
                ++curline; 
                break;
            default:
                if (std::isspace(c)) break;

                is.unget();
                is >> str;
                delimeter_offset = str.find_first_of(delimeter_chars);
                if (delimeter_offset != std::string::npos) {
                    --delimeter_offset;
                    str = str.substr(0, delimeter_offset);
                    is.ignore(delimeter_offset);
                }
                toklist.emplace_back(STRING, curline, str);
                break;
        }
    }
    return toklist;
}
