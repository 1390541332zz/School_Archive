#include "lexer.hpp"

static std::string const err_mismatchParen = "Error: Mismatched Parenthesis on line ";
static std::string const err_mismatchQuote = "Error: Mismatched Quotation mark on line ";

static std::string const delim_chars = "#()\",=";

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
        std::size_t delim_offset = std::string::npos;
        switch(c) {
            case '#':
                SYNTAX_CHECK(toklist, tokstack, curline);
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                is.unget();
                break;
            case '=':
                toklist.emplace_back(EQUAL, curline);
                break;
            case ',':
                toklist.emplace_back(SEP, curline);
                break;
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
               if (!tokstack.empty() && (tokstack.top().line() != curline)) {
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
                if (toklist.empty() || (toklist.back().type() != EOL)) toklist.emplace_back(EOL, curline);
                ++curline; 
                break;
            default:
                if (std::isspace(c)) break;
                is.unget();
                if (!tokstack.empty() && tokstack.top().type() == STRING_DELIM) {
                    std::getline(is, str);
                    delim_offset = str.find_first_of('\"');
                } else {
                    is >> str;
                    delim_offset = str.find_first_of(delim_chars);
                }
                
                if (delim_offset != std::string::npos) {
                    is.seekg(delim_offset - str.size(), std::ios_base::cur);
                    str = str.substr(0, delim_offset);
                }
                toklist.emplace_back(STRING, curline, str);
                break;
        }
    }
    return toklist;
}
