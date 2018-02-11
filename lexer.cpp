#include "lexer.hpp"

static std::string const err_mismatchParen = "Error: Mismatched Parenthesis on line ";
static std::string const err_mismatchQuote = "Error: Mismatched Quotation mark on line ";

static std::string const delim_chars = "#()\",=";

#define SYNTAX_CHECK(TOKLIST, TOKSTACK, CURLINE) do {                                                                  \
    if (!TOKSTACK.empty() && (TOKSTACK.top().type() == STRING_DELIM)) {                                                \
        while (!TOKLIST.empty() && (TOKLIST.back().type() != STRING_DELIM)) {                                          \
            TOKLIST.pop_back();                                                                                        \
        }                                                                                                              \
        TOKLIST.emplace_back(ERROR, CURLINE, err_mismatchQuote + std::to_string(CURLINE));                             \
        return TOKLIST;                                                                                                \
    } else if (!TOKSTACK.empty()) {                                                                                    \
        while (!TOKLIST.empty() && (TOKLIST.back().type() != OPEN_PAREN)) {                                            \
            TOKLIST.pop_back();                                                                                        \
        }                                                                                                              \
        TOKLIST.emplace_back(ERROR, CURLINE, err_mismatchParen + std::to_string(CURLINE));                             \
        return TOKLIST;                                                                                                \
    }                                                                                                                  \
} while (0);


// tokenize: Parses a MIPS assembly text stream into a TokenList for later consumption
//
// Theory: tokenize() is essentially a giant state machine. States are recorded in a list and stack
//         of tokens, a line counter and the input stream. The input stream while not really a 
//         state device, contains the current data and record of surrounding text. The list 
//         contains all previously parsed tokens, the stack contains tokens that must have 
//         matching partners and obviously the line counter contains the current line.
//
//         The STRING_DELIM '"' and OPEN_PAREN '(' are the only two types that should normally be 
//         present in the stack and normally there is only one object on the stack. Due to this, the
//         stack could technically be replaced with a single storage variable however utilising a stack
//         makes future modifications easier given new syntaxes. Additionally the use of the stack
//         provides some insight into the intent of certain steps without the need to explicitly 
//         document them. (for example a stack being empty)
//
//         The list is mostly append only however it has the special case of when errors arise.
//         When errors do arise, tokens are removed from the end of the list until the first token 
//         that triggered the error is at the end of the list. At this point, the error is appended
//         to the end.
//
// Technical Debt: Some of tokenize()'s switch cases could and probably should be spun off into their
//         functions and / or tokenize should be redesigned as a class that parses the text stream and
//         holds ownership over the generated TokenList. 
//
//         Additionally, better state tracking would allow for less convoluted back tracking for handling 
//         parsing errors.
//
//         Another potential source of debt is the awkward cases of blank STRINGs sandwiched between 
//         STRING_DELIMs '"' and EOLs being discarded when an EOL is already the last token in the 
//         list. Similarly the Milestone 0 project spec does not fully address the MIPS 1.0 syntax and
//         therefore will likely run into issues with real world human input and parsing malformed 
//         assembly files. This will likely result in much of the error handling being passed to later
//         stages of the pipeline further complicating future development.
//
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
                    if (toklist.back().type() == STRING_DELIM) toklist.emplace_back(STRING, curline, "");
                    tokstack.pop();
                } else {
                    tokstack.emplace(STRING_DELIM, curline);
                }
                toklist.emplace_back(STRING_DELIM, curline);
                break;
            case '\n':
                SYNTAX_CHECK(toklist, tokstack, curline);
                if (!toklist.empty() && (toklist.back().type() != EOL)) toklist.emplace_back(EOL, curline);
                ++curline; 
                break;
            default:
                if (std::isspace(c)) break;
                is.unget();
                if (!tokstack.empty() && (tokstack.top().type() == STRING_DELIM)) {
                    std::getline(is, str);
                    delim_offset = str.find_first_of("\"#");
                    is.unget();
                    if (is.peek() != '\n') is.ignore();
                } else {
                    is >> str;
                    delim_offset = str.find_first_of(delim_chars);
                }            
                if (delim_offset != std::string::npos) {
                    std::ios::streampos off = delim_offset - static_cast<std::ios::streampos>(str.size());
                    is.seekg(off, std::ios_base::cur);
                    str = str.substr(0, delim_offset);
                }
                toklist.emplace_back(STRING, curline, str);
                break;
        }
    }
    if (!toklist.empty() && (toklist.back().type() != EOL))  toklist.emplace_back(EOL, curline); 
    return toklist;
}
